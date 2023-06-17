COMMENT
/**
 * @file DetGABAAB.mod
 * @brief Adapted from ProbGABAA_EMS.mod by Eilif, Michael and Srikanth
 * @author chindemi
 * @date 2014-05-25
 * @remark Copyright (c) BBP/EPFL 2005-2021. This work is licenced under Creative Common CC BY-NC-SA-4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/)
 * Several changes have been made from the orginal version of this synapse by Greg Glickert to better adapt the model for Large Scale BMTk/Neuron models
 */
ENDCOMMENT


TITLE GABAA and GABAB receptor with presynaptic short-term plasticity


COMMENT
GABAA and GABAB receptor conductance using a dual-exponential profile
presynaptic short-term plasticity based on Fuhrmann et al. 2002, deterministic
version.
ENDCOMMENT


NEURON {
    THREADSAFE

    POINT_PROCESS int2pyr
    RANGE initW     : synaptic scaler for large scale networks added by Greg
    RANGE tau_r_GABAA, tau_d_GABAA
    RANGE Use, u, Dep, Fac, u0, GABAB_ratio
    RANGE i, i_GABAA,  g_GABAA,  g, e_GABAA, gmax
    NONSPECIFIC_CURRENT i
    RANGE synapseID, verboseLevel
    RANGE conductance
    GLOBAL nc_type_param
    : For debugging
    :RANGE sgid, tgid
}


PARAMETER {
    initW        = 2       : added by Greg Glickert to scale synaptic weight for large scale modeling
    tau_r_GABAA  = 1   (ms) : dual-exponential conductance profile
    tau_d_GABAA  = 6     (ms) : IMPORTANT: tau_r < tau_d
 
    Use          = 1.0   (1)  : Utilization of synaptic efficacy
    Dep          = 100   (ms) : relaxation time constant from depression
    Fac          = 10    (ms) :  relaxation time constant from facilitation
    e_GABAA      = -70   (mV) : GABAA reversal potential was -80mv change to -75 never heard of e_gaba not -75 - Greg
    gmax         = .002  (uS) : weight conversion factor (from nS to uS)
    u0           = 0          :initial value of u, which is the running value of release probability
    synapseID    = 0
    verboseLevel = 0
    conductance  = 0.0
    nc_type_param = 7
}


ASSIGNED {
    v (mV)
    i (nA)
    i_GABAA (nA)

    g_GABAA (uS)

    g (uS)

}



STATE {
    A_GABAA       : GABAA state variable to construct the dual-exponential profile - decays with conductance tau_r_GABAA
    B_GABAA       : GABAA state variable to construct the dual-exponential profile - decays with conductance tau_d_GABAA


}


INITIAL{
    LOCAL tp_GABAA, tp_GABAB

    A_GABAA = 0
    B_GABAA = 0



    tp_GABAA = (tau_r_GABAA*tau_d_GABAA)/(tau_d_GABAA-tau_r_GABAA)*log(tau_d_GABAA/tau_r_GABAA) :time to peak of the conductance



}


BREAKPOINT {
    SOLVE state METHOD cnexp
    g_GABAA = gmax*(B_GABAA-A_GABAA) :compute time varying conductance as the difference of state variables B_GABAA and A_GABAA
   
    g = g_GABAA 
    i_GABAA = g_GABAA*(v-e_GABAA) :compute the GABAA driving force based on the time varying conductance, membrane potential, and GABAA reversal

    i = (i_GABAA) * initW
}


DERIVATIVE state{
    A_GABAA' = -A_GABAA/tau_r_GABAA
    B_GABAA' = -B_GABAA/tau_d_GABAA
}


NET_RECEIVE (weight, weight_GABAA, R, Pr, u, tsyn (ms), nc_type){
    LOCAL result
    weight_GABAA = weight


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

    u = Use
    Pr  = u * R                    

    if( verboseLevel > 0 ) {
        printf("Synapse %f at time %g: R = %g Pr = %g erand = %g\n", synapseID, t, R, Pr, result )
    }

    tsyn = t

    A_GABAA = A_GABAA + Pr*weight_GABAA
    B_GABAA = B_GABAA + Pr*weight_GABAA


    if( verboseLevel > 0 ) {
        printf( " vals %g %g %g %g\n", A_GABAA, weight_GABAA, weight )
    }
}


FUNCTION toggleVerbose() {
    verboseLevel = 1-verboseLevel
}
