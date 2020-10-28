#include "rk_int.h"


vector<double> vec_sum(vector<double> vec, double sum){
	int vsize = vec.size();
	for (int i = 0; i < vsize; i++){
		vec[i] += sum;
	}

	return vec;	
}


rk_int :: rk::rk(){
	float t_step = 0.1;
}


double rk_int :: rk::rk4_step(double (*f)(double,vector<double>)  , double y_i, vector<double> y_n, double t_n){
  
  double k1 = (*f)(t_n, y_n);
  double k2 =  (*f)(t_n + t_step*0.5, vec_sum(y_n, k1*0.5));
  double k3 =  (*f)(t_n + t_step*0.5, vec_sum(y_n, k2*0.5));
  double k4 =  (*f)(t_n + t_step    , vec_sum(y_n, k3));

	return y_i + t_step*(k1 + 2.*k2 + 2.*k3 + k4)/6.; 
}


/* double rk_int :: rk::rk6_step(double f (double,vector<double>), double y_i, vector<double> y_n, double t_n){ */

/* 	double k1 = f(t_n,y_n); */
/* 	double k2 = f(t_n + (1./4.)*t_step  , vec_sum(y_n, (1./4.)*k1*t_step)); */
/* 	double k3 = f(t_n + (3./8.)*t_step  , vec_sum(y_n, (3./32.)*t_step*(k1 + 3*k2))); */
/* 	double k4 = f(t_n + (12./13.)*t_step, vec_sum(y_n, (12./2197.)*t_step*(161*k1 - 600*k2 + 608*k3))); */
/* 	double k5 = f(t_n + t_step          , vec_sum(y_n, (1./4104.)*t_step*(8341*k1 - 32832*k2 + 29440*k3 - 845*k4))); */
/* 	double k6 = f(t_n + (0.5)*t_step    , vec_sum(y_n, t_step*(-(8./27.)*k1 + 2*k2 - (3544./2565.)*k3 + (1859./4104.)*k4 - (11./40.)*k5))); */

/* 	return y_i + t_step*((16./27.)*k1 + (6656./2565.)*k3 + (28561./11286.)*k4 - (9./10.)*k5 + (2./11.)*k6)/5.; */
/* } */

/* double rk_int :: rk::rk8_step(double f (double,vector<double>), double y_i, vector<double> y_n, double t_n){ */

/* 	double k_1 = f(t_n, y_n); */
/* 	double k_2 = f(t_n + t_step*(4./27.), vec_sum(y_n, (t_step*4./27.)*k_1)); */                                                  
/* 	double k_3 = f(t_n + t_step*(2./9.) , vec_sum(y_n, (t_step/18.)*(k_1 + 3.*k_2))); */                                           
/* 	double k_4 = f(t_n + t_step*(1./3.) , vec_sum(y_n, (t_step/12.)*(k_1 + 3.*k_3))); */                                          
/* 	double k_5 = f(t_n + t_step*(1./2.) , vec_sum(y_n, (t_step/8.)*(k_1 + 3.*k_4))); */                                          
/* 	double k_6 = f(t_n + t_step*(2./3.) , vec_sum(y_n, (t_step/54.)*(13.*k_1 - 27.*k_3 + 42.*k_4 + 8.*k_5))); */                         
/* 	double k_7 = f(t_n + t_step*(1./6.) , vec_sum(y_n, (t_step/4320.)*(389.*k_1 - 54.*k_3 + 966.*k_4 - 824.*k_5 + 243.*k_6))); */             
/* 	double k_8 = f(t_n + t_step         , vec_sum(y_n, (t_step/20.)*(-234.*k_1 + 81.*k_3 - 1164.*k_4 + 656.*k_5 - 122.*k_6 + 800.*k_7))); */   
/* 	double k_9 = f(t_n + t_step*(5./6.) , vec_sum(y_n, (t_step/288.)*(-127.*k_1 + 18.*k_3 - 678.*k_4 + 456.*k_5 - 9.*k_6 + 576.*k_7 + 4.*k_8))); */
/* 	double k_10= f(t_n + t_step         , vec_sum(y_n, (t_step/820.)*(1481.*k_1 - 81.*k_3 + 7104.*k_4-3376.*k_5 + 72.*k_6 - 5040.*k_7 - 60.*k_8 + 720.*k_9))); */

/* 	return y_i + t_step*(41.*k_1 + 27.*k_4 + 272.*k_5 + 27.*k_6 + 216.*k_7 + 216.*k_9 + 41.*k_10)/840.; */
/* } */

vector<double> rk_int :: rk::eval_v_step(vector<double (*)(double,vector<double>)> f_syst, vector<double> y_n, double t_n){	
	vector<double> y_np1;

	int vsize = f_syst.size();
	for (int i=0; i < vsize; i++){
	  y_np1.push_back(rk4_step(f_syst[i], y_n[i], y_n, t_n));
	}	

	y_np1.push_back(t_n);
	return y_np1;
}

vector<vector<double>> rk_int :: rk::odint_rk4(vector<double (*)(double,vector<double>)> f_syst, vector<double> c_0, double t_f){

	vector<vector<double>> syst_states = {c_0};
	print_tevol(c_0);	

	for (double t = c_0.back(); t < t_f; t += t_step){
		
		vector<double> curr_state = syst_states.back();	
		vector<double> c_i = vector<double> (curr_state.begin(), curr_state.end() - 1);
		
		vector<double> next_state = eval_v_step(f_syst, c_i, t);

		print_tevol(next_state);

		syst_states.push_back(next_state);
	}

	return syst_states; 
}

void rk_int :: rk::set_tstep(double n_tstep){
	t_step = n_tstep;	
	cout << "Time step set to: " << t_step << endl;
}

void rk_int :: rk::print_tevol(vector<double> c_n){
	int vsize = c_n.size();
	for (int i = 0; i < (vsize - 1); i++){
		cout << c_n[i] << ",";
	}
	cout << c_n.back() << endl;
}
