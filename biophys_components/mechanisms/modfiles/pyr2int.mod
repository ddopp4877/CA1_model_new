COMMENT
/**
 * @file DetAMPANMDA.mod
 * @brief Adapted from ProbAMPANMDA_EMS.mod by Eilif, Michael and Srikanth
 * @author chindemi
 * @date 2014-05-25
 * @remark Copyright (c) BBP/EPFL 2005-2021. This work is licenced under Creative Common CC BY-NC-SA-4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/)
* Several changes have been made from the orginal version of this synapse by Greg Glickert to better adapt the model for Large Scale BMTk/Neuron models
 */
ENDCOMMENT


TITLE AMPA and NMDA receptor with presynaptic short-term plasticity


COMMENT
AMPA and NMDA receptor conductance using a dual-exponential profile
presynaptic short-term plasticity based on Fuhrmann et al. 2002, deterministic
version.
ENDCOMMENT


NEURON {
    THREADSAFE

    POINT_PROCESS pyr2int
    RANGE initW     : synaptic scaler for large scale networks added by Greg
    RANGE tau_r_AMPA, tau_d_AMPA, tau_r_NMDA, tau_d_NMDA
    RANGE Use, u, Dep, Fac, u0, mg, NMDA_ratio
    RANGE i, i_AMPA, i_NMDA, g_AMPA, g_NMDA, g, e,gmax
    NONSPECIFIC_CURRENT i
    RANGE synapseID, verboseLevel
    RANGE conductance
    GLOBAL nc_type_param
    : For debugging
    :RANGE sgid, tgid
}


PARAMETER {
    initW         = 1.0      : added by Greg Glickert to scale synaptic weight for large scale modeling
    tau_r_AMPA = 1.5   (ms)  : Dual-exponential conductance profile
    tau_d_AMPA = 1.7   (ms)  : IMPORTANT: tau_r < tau_d
    tau_r_NMDA = 1.5
      (ms)  : Dual-exponential conductance profile
    tau_d_NMDA = 20    (ms)  : IMPORTANT: tau_r < tau_d
    Use = 1.0          (1)   : Utilization of synaptic efficacy
    Dep = 100          (ms)  : Relaxation time constant from depression
    Fac = 10           (ms)  : Relaxation time constant from facilitation
    e = 0              (mV)  : AMPA and NMDA reversal potential
    mg = 1             (mM)  : Initial concentration of mg2+
    gmax = .45        (uS)  : Weight conversion factor (from nS to uS)
    u0 = 0                   : Initial value of u, which is the running value of Use
    NMDA_ratio = 0.71  (1)   : The ratio of NMDA to AMPA
    synapseID = 0
    verboseLevel = 0
    conductance = 0.0
    nc_type_param = 7

}


ASSIGNED {
    v (mV)
    i (nA)
    i_AMPA (nA)
    i_NMDA (nA)
    g_AMPA (uS)
    g_NMDA (uS)
    g (uS)

    mggate
}


STATE {
    A_AMPA       : AMPA state variable to construct the dual-exponential profile - decays with conductance tau_r_AMPA
    B_AMPA       : AMPA state variable to construct the dual-exponential profile - decays with conductance tau_d_AMPA
    A_NMDA       : NMDA state variable to construct the dual-exponential profile - decays with conductance tau_r_NMDA
    B_NMDA       : NMDA state variable to construct the dual-exponential profile - decays with conductance tau_d_NMDA
}


INITIAL{
    LOCAL tp_AMPA, tp_NMDA

    A_AMPA = 0
    B_AMPA = 0

    A_NMDA = 0
    B_NMDA = 0

    tp_AMPA = (tau_r_AMPA*tau_d_AMPA)/(tau_d_AMPA-tau_r_AMPA)*log(tau_d_AMPA/tau_r_AMPA) :time to peak of the conductance
    tp_NMDA = (tau_r_NMDA*tau_d_NMDA)/(tau_d_NMDA-tau_r_NMDA)*log(tau_d_NMDA/tau_r_NMDA) :time to peak of the conductance



}


BREAKPOINT {
    SOLVE state METHOD cnexp
    mggate = 1 / (1 + exp(0.062 (/mV) * -(v)) * (mg / 3.57 (mM))) :mggate kinetics - Jahr & Stevens 1990
    g_AMPA = gmax*(B_AMPA-A_AMPA) :compute time varying conductance as the difference of state variables B_AMPA and A_AMPA
    g_NMDA = gmax*(B_NMDA-A_NMDA) * mggate :compute time varying conductance as the difference of state variables B_NMDA and A_NMDA and mggate kinetics
    g = g_AMPA + g_NMDA
    i_AMPA = g_AMPA*(v-e) * initW :compute the AMPA driving force based on the time varying conductance, membrane potential, and AMPA reversal
    i_NMDA = g_NMDA*(v-e) * initW :compute the NMDA driving force based on the time varying conductance, membrane potential, and NMDA reversal
    i = i_AMPA + i_NMDA
}


DERIVATIVE state{
    A_AMPA' = -A_AMPA/tau_r_AMPA
    B_AMPA' = -B_AMPA/tau_d_AMPA
    A_NMDA' = -A_NMDA/tau_r_NMDA
    B_NMDA' = -B_NMDA/tau_d_NMDA
}


NET_RECEIVE (weight, weight_AMPA, weight_NMDA, R, Pr, u, tsyn (ms), nc_type){
    LOCAL result
    weight_AMPA = weight
    weight_NMDA = weight * NMDA_ratio

    INITIAL{
        R=1
        u=u0
        tsyn=t
    }

    : Disable in case of t < 0 (in case of ForwardSkip) which causes numerical
    : instability if synapses are activated.
    if(t < 0 ) {
    VERBATIM
        return;
    ENDVERBATIM
    }

    if (flag == 1) {
        : self event to set next weight at delay
          weight = conductance

    }
    : flag == 0, i.e. a spike has arrived

    : calc u at event-
    u = Use

    Pr  = u * R                         :Pr is calculated as R * u (running value of Use)


    :if( verboseLevel > 0 ) {
        :printf("Synapse %f at time %g: R = %g Pr = %g erand = %g\n", synapseID, t, R, Pr, result )
    :}

    tsyn = t

    A_AMPA = A_AMPA + Pr*weight_AMPA
    B_AMPA = B_AMPA + Pr*weight_AMPA
    A_NMDA = A_NMDA + Pr*weight_NMDA
    B_NMDA = B_NMDA + Pr*weight_NMDA

    if( verboseLevel > 0 ) {
        printf( " vals %g %g %g %g\n", A_AMPA, weight_AMPA, weight )
    }
}


FUNCTION toggleVerbose() {
    verboseLevel = 1-verboseLevel
}
