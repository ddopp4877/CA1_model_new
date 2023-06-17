:Interneuron Cells to Pyramidal Cells GABA with local Ca2+ pool and read public soma Ca2+ pool

NEURON {
	POINT_PROCESS int2int
	USEION ca READ eca,ica
	NONSPECIFIC_CURRENT igaba
	RANGE initW
	RANGE Cdur_gaba, AlphaTmax_gaba, Beta_gaba, Erev_gaba, gbar_gaba, W, on_gaba, g_gaba
	RANGE eca, tauCa, Icatotal
	RANGE ICag, P0g, fCag
	RANGE Cainf, pooldiam, z
	RANGE lambda1, lambda2, threshold1, threshold2
	RANGE fmax, fmin, Wmax, Wmin, maxChange, normW, scaleW, srcid, destid,limitW
	RANGE pregid,postgid, thr_rp
	RANGE F, f, tauF, D1, d1, tauD1, D2, d2, tauD2
	RANGE facfactor
    RANGE neuroM,type
}

UNITS {
	(mV) = (millivolt)
        (nA) = (nanoamp)
	(uS) = (microsiemens)
	FARADAY = 96485 (coul)
	pi = 3.141592 (1)
}

PARAMETER {

	srcid = -1 (1)
	destid = -1 (1)
	type = -1
	
	Cdur_gaba = 0.7254 (ms)
	AlphaTmax_gaba = 1.52 (/ms):7.2609 (/ms): 2.2609 (/ms): 3.2609 (/ms)   : 7.2609 as original
	Beta_gaba = 0.14(/ms) : 0.147 (/ms) : 0.2667 (/ms):         : 0.2667 as original
	Erev_gaba = -75 (mV) : -75 as original
	gbar_gaba = 0.6e-3 (uS)

	Cainf = 50e-6 (mM)
	pooldiam =  1.8172 (micrometer)
	z = 2

    neuroM = 0
	k = 0.01	
	
	tauCa = 50 (ms)
	
	P0g = .01
	fCag = .024
	
	lambda1 = 1 : 0.7 : 0.6 : 0.7 : 1.0 : 0.5 : 1.5 :3 : 4 : 3 : 2 : 3.0 : 2.0
	lambda2 = .01
	threshold1 = 0.5  :0.47 :  0.48 : 0.45 : 0.4 : 0.95 : 1.35 :0.75 :0.55 (uM)
	threshold2 = 0.6 :0.52 :  0.53 : 0.5 : 0.45 : 1.0 : 1.4 : 0.8 : 0.65 :0.70 (uM)

	:GABA Weight
	initW = 5.0 : 3.0 : 4.0 : 5.0 : 4.2 : 3.5 :4.5 : :  :  3 :  2.5 : 5
	fmax = 3 : 2.85 :4 : 3 : 3
	fmin = .8
	
	GAPstart1 = 96000 
	GAPstop1 = 196000
	
	thr_rp = 1 : .7
	
	facfactor = 1
	: the (1) is needed for the range limits to be effective
        f = 0 (1) < 0, 1e9 > : 1.3 (1) < 0, 1e9 >    : facilitation
        tauF = 20 (ms) < 1e-9, 1e9 >
        d1 = 0.95 (1) < 0, 1 >     : fast depression
        tauD1 = 40 (ms) < 1e-9, 1e9 >
        d2 = 0.9 (1) < 0, 1 >     : slow depression
        tauD2 = 70 (ms) < 1e-9, 1e9 >	
	
    DAstart1 = 39500
	DAstop1 = 40000	
	DAstart2 = 35900
	DAstop2 = 36000	

	DA_t1 = 0.7 : 0.7
	DA_t2 = 1.5 : 1.3 : 1.2
	DA_t3 = 1.25
	DA_S = 1.6 : 1.8 : 1.8					
	Beta1 = 0.001  (/ms) : 1/decay time for neuromodulators
	Beta2 = 0.0001  (/ms)	
	
	NEstart1 = 39500
	NEstop1 = 40000	
	NEstart2 = 35900
	NEstop2 = 36000		


	NE_t1 = 1 : 1 : 0.95

	NE_t2 = 1 :1 : 0.7 : 0.8
	NE_t3 = 1
	NE_S = 1 : 0.4
}

ASSIGNED {
	v (mV)
	eca (mV)
	ica (nA)
	
	igaba (nA)
	g_gaba (uS)
	on_gaba

	limitW

	t0 (ms)

	ICan (nA)
	ICag (nA)
	Afactor	(mM/ms/nA)
	Icatotal (nA)

	dW_gaba
	Wmax
	Wmin
	maxChange
	normW
	scaleW
	
	pregid
	postgid

	rp
	tsyn
	
	fa
	F
	D1
	D2	
}

STATE { r_nmda r_gaba capoolcon W }

INITIAL {

	on_gaba = 0
	r_gaba = 0
	W = initW
	limitW = 1

	t0 = -1

	Wmax = fmax*initW
	Wmin = fmin*initW
	maxChange = (Wmax-Wmin)/10
	dW_gaba = 0

	capoolcon = Cainf
	Afactor	= 1/(z*FARADAY*4/3*pi*(pooldiam/2)^3)*(1e6)

	fa =0
	F = 1
	D1 = 1
	D2 = 1	
}

BREAKPOINT {
if ((eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W))>0&&W>=Wmax) {
        limitW=1e-12
	} else if ((eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W))<0&&W<=Wmin) {
        limitW=1e-12
	} else {
	limitW=1 }
	
	SOLVE release METHOD cnexp
	 : if (W >= Wmax || W <= Wmin ) {     : for limiting the weight
	 : limitW=1e-12
	 : } else {
	  : limitW=1
	 : }
	 :if (W > Wmax) { 
		:W = Wmax
	:} else if (W < Wmin) {
 		:W = Wmin
	:}
	 
	    if (neuroM==1) {
	g_gaba = gbar_gaba*r_gaba*facfactor   : Dopamine effect on GABA	
	} else if (neuroM==2) {
	g_gaba = gbar_gaba*r_gaba*facfactor   : Norepinephrine effect on GABA		    	
	} else if (neuroM==3) {
	g_gaba = gbar_gaba*r_gaba*facfactor  : Dopamine & Norepinephrine effect on GABA		    
	} else {
	g_gaba = gbar_gaba*r_gaba*facfactor
	}

    igaba = W*g_gaba*(v - Erev_gaba)

	ICag = P0g*g_gaba*(v - eca)	
	Icatotal = ICag + k*ica*4*pi*((15/2)^2)*(0.01)    :  icag+k*ica*Area of soma*unit change

	
}

DERIVATIVE release {
    
	: W' = eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W)	  : Long-term plasticity was implemented. (Shouval et al. 2002a, 2002b)
    
	
	W' = 1e-12*limitW*eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W)
	
	r_gaba' = AlphaTmax_gaba*on_gaba*(1-r_gaba)-Beta_gaba*r_gaba
    capoolcon'= -fCag*Afactor*Icatotal + (Cainf-capoolcon)/tauCa		
}

NET_RECEIVE(dummy_weight) {
      if (flag==0) {           :a spike arrived, start onset state if not already on
         if ((!on_gaba)){       :this synpase joins the set of synapses in onset state
           t0=t
	      on_gaba=1		
	      net_send(Cdur_gaba,1)  
         } else if (on_gaba==1) {             :already in onset state, so move offset time
          net_move(t+Cdur_gaba)
		  t0=t
	      }
         }		  
	if (flag == 1) { : turn off transmitter, i.e. this synapse enters the offset state	
	on_gaba=0
    }
	
if (flag == 0) {  : Short term plasticity was implemented(Varela et. al 1997):
	rp = unirand()	
	
	:F  = 1 + (F-1)* exp(-(t - tsyn)/tauF)
	D1 = 1 - (1-D1)*exp(-(t - tsyn)/tauD1)
	D2 = 1 - (1-D2)*exp(-(t - tsyn)/tauD2)
 :printf("%g\t%g\t%g\t%g\t%g\t%g\n", t, t-tsyn, F, D1, D2, facfactor)
	:printf("%g\t%g\t%g\t%g\n", F, D1, D2, facfactor)
	tsyn = t
	
	facfactor = 1:F * D1 * D2

	::F = F+f  :F * f
	
	if (F > 3) { 
	F=3	}	
	if (facfactor < 0.7) { 
	facfactor=0.7
	}
	D1 = D1 * d1
	D2 = D2 * d2
:printf("\t%g\t%g\t%g\n", F, D1, D2)
}
}

:::::::::::: FUNCTIONs and PROCEDUREs ::::::::::::

FUNCTION eta(Cani (mM)) {
	LOCAL taulearn, P1, P2, P4, Cacon
	P1 = 0.1
	P2 = P1*1e-4
	P4 = 1
	Cacon = Cani*1e3
	taulearn = P1/(P2+Cacon*Cacon*Cacon)+P4
	eta = 1/taulearn*0.001
}

FUNCTION omega(Cani (mM), threshold1 (uM), threshold2 (uM)) {
	LOCAL r, mid, Cacon
	Cacon = Cani*1e3
	r = (threshold2-threshold1)/2
	mid = (threshold1+threshold2)/2
	if (Cacon <= threshold1) { omega = 0}
	else if (Cacon >= threshold2) {	omega = 1/(1+50*exp(-50*(Cacon-threshold2)))}
	else {omega = -sqrt(r*r-(Cacon-mid)*(Cacon-mid))}
}

FUNCTION GAP1(GAPstart1 (ms), GAPstop1 (ms)) {
	LOCAL s
	if (t <= GAPstart1) { GAP1 = 1}
	else if (t >= GAPstop1 ) {GAP1 = 1}					: During the Gap, apply lamda2*2
	else  {	GAP1 = 1}
}
FUNCTION unirand() {    : uniform random numbers between 0 and 1
        unirand = scop_random()
}
