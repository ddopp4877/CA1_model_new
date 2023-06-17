/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__int2int
#define _nrn_initial _nrn_initial__int2int
#define nrn_cur _nrn_cur__int2int
#define _nrn_current _nrn_current__int2int
#define nrn_jacob _nrn_jacob__int2int
#define nrn_state _nrn_state__int2int
#define _net_receive _net_receive__int2int 
#define release release__int2int 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define srcid _p[0]
#define destid _p[1]
#define type _p[2]
#define Cdur_gaba _p[3]
#define AlphaTmax_gaba _p[4]
#define Beta_gaba _p[5]
#define Erev_gaba _p[6]
#define gbar_gaba _p[7]
#define Cainf _p[8]
#define pooldiam _p[9]
#define z _p[10]
#define neuroM _p[11]
#define tauCa _p[12]
#define P0g _p[13]
#define fCag _p[14]
#define lambda1 _p[15]
#define lambda2 _p[16]
#define threshold1 _p[17]
#define threshold2 _p[18]
#define initW _p[19]
#define fmax _p[20]
#define fmin _p[21]
#define thr_rp _p[22]
#define facfactor _p[23]
#define f _p[24]
#define tauF _p[25]
#define d1 _p[26]
#define tauD1 _p[27]
#define d2 _p[28]
#define tauD2 _p[29]
#define igaba _p[30]
#define g_gaba _p[31]
#define on_gaba _p[32]
#define limitW _p[33]
#define ICag _p[34]
#define Icatotal _p[35]
#define Wmax _p[36]
#define Wmin _p[37]
#define maxChange _p[38]
#define normW _p[39]
#define scaleW _p[40]
#define pregid _p[41]
#define postgid _p[42]
#define F _p[43]
#define D1 _p[44]
#define D2 _p[45]
#define r_nmda _p[46]
#define r_gaba _p[47]
#define capoolcon _p[48]
#define W _p[49]
#define eca _p[50]
#define ica _p[51]
#define t0 _p[52]
#define ICan _p[53]
#define Afactor _p[54]
#define dW_gaba _p[55]
#define rp _p[56]
#define tsyn _p[57]
#define fa _p[58]
#define Dr_nmda _p[59]
#define Dr_gaba _p[60]
#define Dcapoolcon _p[61]
#define DW _p[62]
#define _g _p[63]
#define _tsav _p[64]
#define _nd_area  *_ppvar[0]._pval
#define _ion_eca	*_ppvar[2]._pval
#define _ion_ica	*_ppvar[3]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_GAP1();
 static double _hoc_eta();
 static double _hoc_omega();
 static double _hoc_unirand();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "GAP1", _hoc_GAP1,
 "eta", _hoc_eta,
 "omega", _hoc_omega,
 "unirand", _hoc_unirand,
 0, 0
};
#define GAP1 GAP1_int2int
#define eta eta_int2int
#define omega omega_int2int
#define unirand unirand_int2int
 extern double GAP1( double , double );
 extern double eta( double );
 extern double omega( double , double , double );
 extern double unirand( );
 /* declare global and static user variables */
#define Beta2 Beta2_int2int
 double Beta2 = 0.0001;
#define Beta1 Beta1_int2int
 double Beta1 = 0.001;
#define DA_S DA_S_int2int
 double DA_S = 1.6;
#define DA_t3 DA_t3_int2int
 double DA_t3 = 1.25;
#define DA_t2 DA_t2_int2int
 double DA_t2 = 1.5;
#define DA_t1 DA_t1_int2int
 double DA_t1 = 0.7;
#define DAstop2 DAstop2_int2int
 double DAstop2 = 36000;
#define DAstart2 DAstart2_int2int
 double DAstart2 = 35900;
#define DAstop1 DAstop1_int2int
 double DAstop1 = 40000;
#define DAstart1 DAstart1_int2int
 double DAstart1 = 39500;
#define GAPstop1 GAPstop1_int2int
 double GAPstop1 = 196000;
#define GAPstart1 GAPstart1_int2int
 double GAPstart1 = 96000;
#define NE_S NE_S_int2int
 double NE_S = 1;
#define NE_t3 NE_t3_int2int
 double NE_t3 = 1;
#define NE_t2 NE_t2_int2int
 double NE_t2 = 1;
#define NE_t1 NE_t1_int2int
 double NE_t1 = 1;
#define NEstop2 NEstop2_int2int
 double NEstop2 = 36000;
#define NEstart2 NEstart2_int2int
 double NEstart2 = 35900;
#define NEstop1 NEstop1_int2int
 double NEstop1 = 40000;
#define NEstart1 NEstart1_int2int
 double NEstart1 = 39500;
#define k k_int2int
 double k = 0.01;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "d2", 0, 1,
 "d1", 0, 1,
 "f", 0, 1e+09,
 "tauD2", 1e-09, 1e+09,
 "tauD1", 1e-09, 1e+09,
 "tauF", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Beta1_int2int", "/ms",
 "Beta2_int2int", "/ms",
 "srcid", "1",
 "destid", "1",
 "Cdur_gaba", "ms",
 "AlphaTmax_gaba", "/ms",
 "Beta_gaba", "/ms",
 "Erev_gaba", "mV",
 "gbar_gaba", "uS",
 "Cainf", "mM",
 "pooldiam", "micrometer",
 "tauCa", "ms",
 "f", "1",
 "tauF", "ms",
 "d1", "1",
 "tauD1", "ms",
 "d2", "1",
 "tauD2", "ms",
 "igaba", "nA",
 "g_gaba", "uS",
 "ICag", "nA",
 "Icatotal", "nA",
 0,0
};
 static double W0 = 0;
 static double capoolcon0 = 0;
 static double delta_t = 0.01;
 static double r_gaba0 = 0;
 static double r_nmda0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "k_int2int", &k_int2int,
 "GAPstart1_int2int", &GAPstart1_int2int,
 "GAPstop1_int2int", &GAPstop1_int2int,
 "DAstart1_int2int", &DAstart1_int2int,
 "DAstop1_int2int", &DAstop1_int2int,
 "DAstart2_int2int", &DAstart2_int2int,
 "DAstop2_int2int", &DAstop2_int2int,
 "DA_t1_int2int", &DA_t1_int2int,
 "DA_t2_int2int", &DA_t2_int2int,
 "DA_t3_int2int", &DA_t3_int2int,
 "DA_S_int2int", &DA_S_int2int,
 "Beta1_int2int", &Beta1_int2int,
 "Beta2_int2int", &Beta2_int2int,
 "NEstart1_int2int", &NEstart1_int2int,
 "NEstop1_int2int", &NEstop1_int2int,
 "NEstart2_int2int", &NEstart2_int2int,
 "NEstop2_int2int", &NEstop2_int2int,
 "NE_t1_int2int", &NE_t1_int2int,
 "NE_t2_int2int", &NE_t2_int2int,
 "NE_t3_int2int", &NE_t3_int2int,
 "NE_S_int2int", &NE_S_int2int,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[5]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"int2int",
 "srcid",
 "destid",
 "type",
 "Cdur_gaba",
 "AlphaTmax_gaba",
 "Beta_gaba",
 "Erev_gaba",
 "gbar_gaba",
 "Cainf",
 "pooldiam",
 "z",
 "neuroM",
 "tauCa",
 "P0g",
 "fCag",
 "lambda1",
 "lambda2",
 "threshold1",
 "threshold2",
 "initW",
 "fmax",
 "fmin",
 "thr_rp",
 "facfactor",
 "f",
 "tauF",
 "d1",
 "tauD1",
 "d2",
 "tauD2",
 0,
 "igaba",
 "g_gaba",
 "on_gaba",
 "limitW",
 "ICag",
 "Icatotal",
 "Wmax",
 "Wmin",
 "maxChange",
 "normW",
 "scaleW",
 "pregid",
 "postgid",
 "F",
 "D1",
 "D2",
 0,
 "r_nmda",
 "r_gaba",
 "capoolcon",
 "W",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 65, _prop);
 	/*initialize range parameters*/
 	srcid = -1;
 	destid = -1;
 	type = -1;
 	Cdur_gaba = 0.7254;
 	AlphaTmax_gaba = 1.52;
 	Beta_gaba = 0.14;
 	Erev_gaba = -75;
 	gbar_gaba = 0.0006;
 	Cainf = 5e-05;
 	pooldiam = 1.8172;
 	z = 2;
 	neuroM = 0;
 	tauCa = 50;
 	P0g = 0.01;
 	fCag = 0.024;
 	lambda1 = 1;
 	lambda2 = 0.01;
 	threshold1 = 0.5;
 	threshold2 = 0.6;
 	initW = 5;
 	fmax = 3;
 	fmin = 0.8;
 	thr_rp = 1;
 	facfactor = 1;
 	f = 0;
 	tauF = 20;
 	d1 = 0.95;
 	tauD1 = 40;
 	d2 = 0.9;
 	tauD2 = 70;
  }
 	_prop->param = _p;
 	_prop->param_size = 65;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 6, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[2]._pval = &prop_ion->param[0]; /* eca */
 	_ppvar[3]._pval = &prop_ion->param[3]; /* ica */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 
#define _tqitem &(_ppvar[4]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _int2int_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 65, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "netsend");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 int2int /home/dpd4k4/CA1_model/biophys_components/mechanisms/modfiles/int2int.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.0;
 static double pi = 3.141592;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int release(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   DW = 1e-12 * limitW * eta ( _threadargscomma_ capoolcon ) * ( lambda1 * omega ( _threadargscomma_ capoolcon , threshold1 , threshold2 ) - lambda2 * GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) * W ) ;
   Dr_gaba = AlphaTmax_gaba * on_gaba * ( 1.0 - r_gaba ) - Beta_gaba * r_gaba ;
   Dcapoolcon = - fCag * Afactor * Icatotal + ( Cainf - capoolcon ) / tauCa ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 DW = DW  / (1. - dt*( ( 1e-12 * limitW * eta ( _threadargscomma_ capoolcon ) )*( ( ( - ( lambda2 * GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) )*( 1.0 ) ) ) ) )) ;
 Dr_gaba = Dr_gaba  / (1. - dt*( ( AlphaTmax_gaba * on_gaba )*( ( ( - 1.0 ) ) ) - ( Beta_gaba )*( 1.0 ) )) ;
 Dcapoolcon = Dcapoolcon  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tauCa )) ;
  return 0;
}
 /*END CVODE*/
 static int release () {_reset=0;
 {
    W = W + (1. - exp(dt*(( 1e-12 * limitW * eta ( _threadargscomma_ capoolcon ) )*( ( ( - ( lambda2 * GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) )*( 1.0 ) ) ) ))))*(- ( ( ( ( 1e-12 )*( limitW ) )*( eta ( _threadargscomma_ capoolcon ) ) )*( ( ( lambda1 )*( omega ( _threadargscomma_ capoolcon , threshold1 , threshold2 ) ) ) ) ) / ( ( ( ( 1e-12 )*( limitW ) )*( eta ( _threadargscomma_ capoolcon ) ) )*( ( ( - ( ( lambda2 )*( GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) ) )*( 1.0 ) ) ) ) ) - W) ;
    r_gaba = r_gaba + (1. - exp(dt*(( AlphaTmax_gaba * on_gaba )*( ( ( - 1.0 ) ) ) - ( Beta_gaba )*( 1.0 ))))*(- ( ( ( AlphaTmax_gaba )*( on_gaba ) )*( ( 1.0 ) ) ) / ( ( ( AlphaTmax_gaba )*( on_gaba ) )*( ( ( - 1.0 ) ) ) - ( Beta_gaba )*( 1.0 ) ) - r_gaba) ;
    capoolcon = capoolcon + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tauCa)))*(- ( ( ( - fCag )*( Afactor ) )*( Icatotal ) + ( ( Cainf ) ) / tauCa ) / ( ( ( ( - 1.0 ) ) ) / tauCa ) - capoolcon) ;
   }
  return 0;
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 0.0 ) {
     if ( (  ! on_gaba ) ) {
       t0 = t ;
       on_gaba = 1.0 ;
       net_send ( _tqitem, _args, _pnt, t +  Cdur_gaba , 1.0 ) ;
       }
     else if ( on_gaba  == 1.0 ) {
       net_move ( _tqitem, _pnt, t + Cdur_gaba ) ;
       t0 = t ;
       }
     }
   if ( _lflag  == 1.0 ) {
     on_gaba = 0.0 ;
     }
   if ( _lflag  == 0.0 ) {
     rp = unirand ( _threadargs_ ) ;
     D1 = 1.0 - ( 1.0 - D1 ) * exp ( - ( t - tsyn ) / tauD1 ) ;
     D2 = 1.0 - ( 1.0 - D2 ) * exp ( - ( t - tsyn ) / tauD2 ) ;
     tsyn = t ;
     facfactor = 1.0 ;
     if ( F > 3.0 ) {
       F = 3.0 ;
       }
     if ( facfactor < 0.7 ) {
       facfactor = 0.7 ;
       }
     D1 = D1 * d1 ;
     D2 = D2 * d2 ;
     }
   } }
 
double eta (  double _lCani ) {
   double _leta;
 double _ltaulearn , _lP1 , _lP2 , _lP4 , _lCacon ;
 _lP1 = 0.1 ;
   _lP2 = _lP1 * 1e-4 ;
   _lP4 = 1.0 ;
   _lCacon = _lCani * 1e3 ;
   _ltaulearn = _lP1 / ( _lP2 + _lCacon * _lCacon * _lCacon ) + _lP4 ;
   _leta = 1.0 / _ltaulearn * 0.001 ;
   
return _leta;
 }
 
static double _hoc_eta(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  eta (  *getarg(1) );
 return(_r);
}
 
double omega (  double _lCani , double _lthreshold1 , double _lthreshold2 ) {
   double _lomega;
 double _lr , _lmid , _lCacon ;
 _lCacon = _lCani * 1e3 ;
   _lr = ( _lthreshold2 - _lthreshold1 ) / 2.0 ;
   _lmid = ( _lthreshold1 + _lthreshold2 ) / 2.0 ;
   if ( _lCacon <= _lthreshold1 ) {
     _lomega = 0.0 ;
     }
   else if ( _lCacon >= _lthreshold2 ) {
     _lomega = 1.0 / ( 1.0 + 50.0 * exp ( - 50.0 * ( _lCacon - _lthreshold2 ) ) ) ;
     }
   else {
     _lomega = - sqrt ( _lr * _lr - ( _lCacon - _lmid ) * ( _lCacon - _lmid ) ) ;
     }
   
return _lomega;
 }
 
static double _hoc_omega(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  omega (  *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double GAP1 (  double _lGAPstart1 , double _lGAPstop1 ) {
   double _lGAP1;
 double _ls ;
 if ( t <= _lGAPstart1 ) {
     _lGAP1 = 1.0 ;
     }
   else if ( t >= _lGAPstop1 ) {
     _lGAP1 = 1.0 ;
     }
   else {
     _lGAP1 = 1.0 ;
     }
   
return _lGAP1;
 }
 
static double _hoc_GAP1(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  GAP1 (  *getarg(1) , *getarg(2) );
 return(_r);
}
 
double unirand (  ) {
   double _lunirand;
 _lunirand = scop_random ( ) ;
   
return _lunirand;
 }
 
static double _hoc_unirand(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  unirand (  );
 return(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  eca = _ion_eca;
  ica = _ion_ica;
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  eca = _ion_eca;
  ica = _ion_ica;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 0);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 3);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  W = W0;
  capoolcon = capoolcon0;
  r_gaba = r_gaba0;
  r_nmda = r_nmda0;
 {
   on_gaba = 0.0 ;
   r_gaba = 0.0 ;
   W = initW ;
   limitW = 1.0 ;
   t0 = - 1.0 ;
   Wmax = fmax * initW ;
   Wmin = fmin * initW ;
   maxChange = ( Wmax - Wmin ) / 10.0 ;
   dW_gaba = 0.0 ;
   capoolcon = Cainf ;
   Afactor = 1.0 / ( z * FARADAY * 4.0 / 3.0 * pi * pow( ( pooldiam / 2.0 ) , 3.0 ) ) * ( 1e6 ) ;
   fa = 0.0 ;
   F = 1.0 ;
   D1 = 1.0 ;
   D2 = 1.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  eca = _ion_eca;
  ica = _ion_ica;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   if ( ( eta ( _threadargscomma_ capoolcon ) * ( lambda1 * omega ( _threadargscomma_ capoolcon , threshold1 , threshold2 ) - lambda2 * GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) * W ) ) > 0.0  && W >= Wmax ) {
     limitW = 1e-12 ;
     }
   else if ( ( eta ( _threadargscomma_ capoolcon ) * ( lambda1 * omega ( _threadargscomma_ capoolcon , threshold1 , threshold2 ) - lambda2 * GAP1 ( _threadargscomma_ GAPstart1 , GAPstop1 ) * W ) ) < 0.0  && W <= Wmin ) {
     limitW = 1e-12 ;
     }
   else {
     limitW = 1.0 ;
     }
   if ( neuroM  == 1.0 ) {
     g_gaba = gbar_gaba * r_gaba * facfactor ;
     }
   else if ( neuroM  == 2.0 ) {
     g_gaba = gbar_gaba * r_gaba * facfactor ;
     }
   else if ( neuroM  == 3.0 ) {
     g_gaba = gbar_gaba * r_gaba * facfactor ;
     }
   else {
     g_gaba = gbar_gaba * r_gaba * facfactor ;
     }
   igaba = W * g_gaba * ( v - Erev_gaba ) ;
   ICag = P0g * g_gaba * ( v - eca ) ;
   Icatotal = ICag + k * ica * 4.0 * pi * ( pow( ( 15.0 / 2.0 ) , 2.0 ) ) * ( 0.01 ) ;
   }
 _current += igaba;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  eca = _ion_eca;
  ica = _ion_ica;
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  eca = _ion_eca;
  ica = _ion_ica;
 { error =  release();
 if(error){fprintf(stderr,"at line 182 in file int2int.mod:\n	 \n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(W) - _p;  _dlist1[0] = &(DW) - _p;
 _slist1[1] = &(r_gaba) - _p;  _dlist1[1] = &(Dr_gaba) - _p;
 _slist1[2] = &(capoolcon) - _p;  _dlist1[2] = &(Dcapoolcon) - _p;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/dpd4k4/CA1_model/biophys_components/mechanisms/modfiles/int2int.mod";
static const char* nmodl_file_text = 
  ":Interneuron Cells to Pyramidal Cells GABA with local Ca2+ pool and read public soma Ca2+ pool\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS int2int\n"
  "	USEION ca READ eca,ica\n"
  "	NONSPECIFIC_CURRENT igaba\n"
  "	RANGE initW\n"
  "	RANGE Cdur_gaba, AlphaTmax_gaba, Beta_gaba, Erev_gaba, gbar_gaba, W, on_gaba, g_gaba\n"
  "	RANGE eca, tauCa, Icatotal\n"
  "	RANGE ICag, P0g, fCag\n"
  "	RANGE Cainf, pooldiam, z\n"
  "	RANGE lambda1, lambda2, threshold1, threshold2\n"
  "	RANGE fmax, fmin, Wmax, Wmin, maxChange, normW, scaleW, srcid, destid,limitW\n"
  "	RANGE pregid,postgid, thr_rp\n"
  "	RANGE F, f, tauF, D1, d1, tauD1, D2, d2, tauD2\n"
  "	RANGE facfactor\n"
  "    RANGE neuroM,type\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "        (nA) = (nanoamp)\n"
  "	(uS) = (microsiemens)\n"
  "	FARADAY = 96485 (coul)\n"
  "	pi = 3.141592 (1)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	srcid = -1 (1)\n"
  "	destid = -1 (1)\n"
  "	type = -1\n"
  "	\n"
  "	Cdur_gaba = 0.7254 (ms)\n"
  "	AlphaTmax_gaba = 1.52 (/ms):7.2609 (/ms): 2.2609 (/ms): 3.2609 (/ms)   : 7.2609 as original\n"
  "	Beta_gaba = 0.14(/ms) : 0.147 (/ms) : 0.2667 (/ms):         : 0.2667 as original\n"
  "	Erev_gaba = -75 (mV) : -75 as original\n"
  "	gbar_gaba = 0.6e-3 (uS)\n"
  "\n"
  "	Cainf = 50e-6 (mM)\n"
  "	pooldiam =  1.8172 (micrometer)\n"
  "	z = 2\n"
  "\n"
  "    neuroM = 0\n"
  "	k = 0.01	\n"
  "	\n"
  "	tauCa = 50 (ms)\n"
  "	\n"
  "	P0g = .01\n"
  "	fCag = .024\n"
  "	\n"
  "	lambda1 = 1 : 0.7 : 0.6 : 0.7 : 1.0 : 0.5 : 1.5 :3 : 4 : 3 : 2 : 3.0 : 2.0\n"
  "	lambda2 = .01\n"
  "	threshold1 = 0.5  :0.47 :  0.48 : 0.45 : 0.4 : 0.95 : 1.35 :0.75 :0.55 (uM)\n"
  "	threshold2 = 0.6 :0.52 :  0.53 : 0.5 : 0.45 : 1.0 : 1.4 : 0.8 : 0.65 :0.70 (uM)\n"
  "\n"
  "	:GABA Weight\n"
  "	initW = 5.0 : 3.0 : 4.0 : 5.0 : 4.2 : 3.5 :4.5 : :  :  3 :  2.5 : 5\n"
  "	fmax = 3 : 2.85 :4 : 3 : 3\n"
  "	fmin = .8\n"
  "	\n"
  "	GAPstart1 = 96000 \n"
  "	GAPstop1 = 196000\n"
  "	\n"
  "	thr_rp = 1 : .7\n"
  "	\n"
  "	facfactor = 1\n"
  "	: the (1) is needed for the range limits to be effective\n"
  "        f = 0 (1) < 0, 1e9 > : 1.3 (1) < 0, 1e9 >    : facilitation\n"
  "        tauF = 20 (ms) < 1e-9, 1e9 >\n"
  "        d1 = 0.95 (1) < 0, 1 >     : fast depression\n"
  "        tauD1 = 40 (ms) < 1e-9, 1e9 >\n"
  "        d2 = 0.9 (1) < 0, 1 >     : slow depression\n"
  "        tauD2 = 70 (ms) < 1e-9, 1e9 >	\n"
  "	\n"
  "    DAstart1 = 39500\n"
  "	DAstop1 = 40000	\n"
  "	DAstart2 = 35900\n"
  "	DAstop2 = 36000	\n"
  "\n"
  "	DA_t1 = 0.7 : 0.7\n"
  "	DA_t2 = 1.5 : 1.3 : 1.2\n"
  "	DA_t3 = 1.25\n"
  "	DA_S = 1.6 : 1.8 : 1.8					\n"
  "	Beta1 = 0.001  (/ms) : 1/decay time for neuromodulators\n"
  "	Beta2 = 0.0001  (/ms)	\n"
  "	\n"
  "	NEstart1 = 39500\n"
  "	NEstop1 = 40000	\n"
  "	NEstart2 = 35900\n"
  "	NEstop2 = 36000		\n"
  "\n"
  "\n"
  "	NE_t1 = 1 : 1 : 0.95\n"
  "\n"
  "	NE_t2 = 1 :1 : 0.7 : 0.8\n"
  "	NE_t3 = 1\n"
  "	NE_S = 1 : 0.4\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	eca (mV)\n"
  "	ica (nA)\n"
  "	\n"
  "	igaba (nA)\n"
  "	g_gaba (uS)\n"
  "	on_gaba\n"
  "\n"
  "	limitW\n"
  "\n"
  "	t0 (ms)\n"
  "\n"
  "	ICan (nA)\n"
  "	ICag (nA)\n"
  "	Afactor	(mM/ms/nA)\n"
  "	Icatotal (nA)\n"
  "\n"
  "	dW_gaba\n"
  "	Wmax\n"
  "	Wmin\n"
  "	maxChange\n"
  "	normW\n"
  "	scaleW\n"
  "	\n"
  "	pregid\n"
  "	postgid\n"
  "\n"
  "	rp\n"
  "	tsyn\n"
  "	\n"
  "	fa\n"
  "	F\n"
  "	D1\n"
  "	D2	\n"
  "}\n"
  "\n"
  "STATE { r_nmda r_gaba capoolcon W }\n"
  "\n"
  "INITIAL {\n"
  "\n"
  "	on_gaba = 0\n"
  "	r_gaba = 0\n"
  "	W = initW\n"
  "	limitW = 1\n"
  "\n"
  "	t0 = -1\n"
  "\n"
  "	Wmax = fmax*initW\n"
  "	Wmin = fmin*initW\n"
  "	maxChange = (Wmax-Wmin)/10\n"
  "	dW_gaba = 0\n"
  "\n"
  "	capoolcon = Cainf\n"
  "	Afactor	= 1/(z*FARADAY*4/3*pi*(pooldiam/2)^3)*(1e6)\n"
  "\n"
  "	fa =0\n"
  "	F = 1\n"
  "	D1 = 1\n"
  "	D2 = 1	\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "if ((eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W))>0&&W>=Wmax) {\n"
  "        limitW=1e-12\n"
  "	} else if ((eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W))<0&&W<=Wmin) {\n"
  "        limitW=1e-12\n"
  "	} else {\n"
  "	limitW=1 }\n"
  "	\n"
  "	SOLVE release METHOD cnexp\n"
  "	 : if (W >= Wmax || W <= Wmin ) {     : for limiting the weight\n"
  "	 : limitW=1e-12\n"
  "	 : } else {\n"
  "	  : limitW=1\n"
  "	 : }\n"
  "	 :if (W > Wmax) { \n"
  "		:W = Wmax\n"
  "	:} else if (W < Wmin) {\n"
  " 		:W = Wmin\n"
  "	:}\n"
  "	 \n"
  "	    if (neuroM==1) {\n"
  "	g_gaba = gbar_gaba*r_gaba*facfactor   : Dopamine effect on GABA	\n"
  "	} else if (neuroM==2) {\n"
  "	g_gaba = gbar_gaba*r_gaba*facfactor   : Norepinephrine effect on GABA		    	\n"
  "	} else if (neuroM==3) {\n"
  "	g_gaba = gbar_gaba*r_gaba*facfactor  : Dopamine & Norepinephrine effect on GABA		    \n"
  "	} else {\n"
  "	g_gaba = gbar_gaba*r_gaba*facfactor\n"
  "	}\n"
  "\n"
  "    igaba = W*g_gaba*(v - Erev_gaba)\n"
  "\n"
  "	ICag = P0g*g_gaba*(v - eca)	\n"
  "	Icatotal = ICag + k*ica*4*pi*((15/2)^2)*(0.01)    :  icag+k*ica*Area of soma*unit change\n"
  "\n"
  "	\n"
  "}\n"
  "\n"
  "DERIVATIVE release {\n"
  "    \n"
  "	: W' = eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W)	  : Long-term plasticity was implemented. (Shouval et al. 2002a, 2002b)\n"
  "    \n"
  "	\n"
  "	W' = 1e-12*limitW*eta(capoolcon)*(lambda1*omega(capoolcon, threshold1, threshold2)-lambda2*GAP1(GAPstart1, GAPstop1)*W)\n"
  "	\n"
  "	r_gaba' = AlphaTmax_gaba*on_gaba*(1-r_gaba)-Beta_gaba*r_gaba\n"
  "    capoolcon'= -fCag*Afactor*Icatotal + (Cainf-capoolcon)/tauCa		\n"
  "}\n"
  "\n"
  "NET_RECEIVE(dummy_weight) {\n"
  "      if (flag==0) {           :a spike arrived, start onset state if not already on\n"
  "         if ((!on_gaba)){       :this synpase joins the set of synapses in onset state\n"
  "           t0=t\n"
  "	      on_gaba=1		\n"
  "	      net_send(Cdur_gaba,1)  \n"
  "         } else if (on_gaba==1) {             :already in onset state, so move offset time\n"
  "          net_move(t+Cdur_gaba)\n"
  "		  t0=t\n"
  "	      }\n"
  "         }		  \n"
  "	if (flag == 1) { : turn off transmitter, i.e. this synapse enters the offset state	\n"
  "	on_gaba=0\n"
  "    }\n"
  "	\n"
  "if (flag == 0) {  : Short term plasticity was implemented(Varela et. al 1997):\n"
  "	rp = unirand()	\n"
  "	\n"
  "	:F  = 1 + (F-1)* exp(-(t - tsyn)/tauF)\n"
  "	D1 = 1 - (1-D1)*exp(-(t - tsyn)/tauD1)\n"
  "	D2 = 1 - (1-D2)*exp(-(t - tsyn)/tauD2)\n"
  " :printf(\"%g\\t%g\\t%g\\t%g\\t%g\\t%g\\n\", t, t-tsyn, F, D1, D2, facfactor)\n"
  "	:printf(\"%g\\t%g\\t%g\\t%g\\n\", F, D1, D2, facfactor)\n"
  "	tsyn = t\n"
  "	\n"
  "	facfactor = 1:F * D1 * D2\n"
  "\n"
  "	::F = F+f  :F * f\n"
  "	\n"
  "	if (F > 3) { \n"
  "	F=3	}	\n"
  "	if (facfactor < 0.7) { \n"
  "	facfactor=0.7\n"
  "	}\n"
  "	D1 = D1 * d1\n"
  "	D2 = D2 * d2\n"
  ":printf(\"\\t%g\\t%g\\t%g\\n\", F, D1, D2)\n"
  "}\n"
  "}\n"
  "\n"
  ":::::::::::: FUNCTIONs and PROCEDUREs ::::::::::::\n"
  "\n"
  "FUNCTION eta(Cani (mM)) {\n"
  "	LOCAL taulearn, P1, P2, P4, Cacon\n"
  "	P1 = 0.1\n"
  "	P2 = P1*1e-4\n"
  "	P4 = 1\n"
  "	Cacon = Cani*1e3\n"
  "	taulearn = P1/(P2+Cacon*Cacon*Cacon)+P4\n"
  "	eta = 1/taulearn*0.001\n"
  "}\n"
  "\n"
  "FUNCTION omega(Cani (mM), threshold1 (uM), threshold2 (uM)) {\n"
  "	LOCAL r, mid, Cacon\n"
  "	Cacon = Cani*1e3\n"
  "	r = (threshold2-threshold1)/2\n"
  "	mid = (threshold1+threshold2)/2\n"
  "	if (Cacon <= threshold1) { omega = 0}\n"
  "	else if (Cacon >= threshold2) {	omega = 1/(1+50*exp(-50*(Cacon-threshold2)))}\n"
  "	else {omega = -sqrt(r*r-(Cacon-mid)*(Cacon-mid))}\n"
  "}\n"
  "\n"
  "FUNCTION GAP1(GAPstart1 (ms), GAPstop1 (ms)) {\n"
  "	LOCAL s\n"
  "	if (t <= GAPstart1) { GAP1 = 1}\n"
  "	else if (t >= GAPstop1 ) {GAP1 = 1}					: During the Gap, apply lamda2*2\n"
  "	else  {	GAP1 = 1}\n"
  "}\n"
  "FUNCTION unirand() {    : uniform random numbers between 0 and 1\n"
  "        unirand = scop_random()\n"
  "}\n"
  ;
#endif
