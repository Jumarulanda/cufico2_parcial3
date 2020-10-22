#include "rk_int.h"

rk_int :: rk::rk(){
	float t_step = 0.1;
}


double rk_int :: rk::rk4_step(double f (double,double), double y_n, double t_n){
	double k1 = t_step * f(t_n, y_n);
	double k2 = t_step * f(t_n + t_step*0.5, y_n + k1*0.5);
	double k3 = t_step * f(t_n + t_step*0.5, y_n + k2*0.5);
	double k4 = t_step * f(t_n + t_step    , y_n + k3);

	return y_n + (k1 + 2.*k2 + 2.*k3 + k4)/6.; 
}


vector<double> rk_int :: rk::eval_v_step(vector<double (*)(double,double)> f_syst, vector<double> y_n, double t_n){	
	vector<double> y_np1;

	int vsize = f_syst.size();
	for (int i=0; i < vsize; i++){
		int ssize = y_n.size();
		for (int j=0; j < ssize; j++){
			y_np1.push_back(rk4_step(f_syst[i], y_n[j], t_n));
		}	
	}	

	y_np1.push_back(t_n);
	return y_np1;
}

vector<vector<double>> rk_int :: rk::odint_rk4(vector<double (*)(double,double)> f_syst, vector<double> c_0, double t_f){

	vector<vector<double>> syst_states = {c_0};

	for (double t = c_0.back(); t < t_f; t += t_step){
		
		vector<double> c_i = vector<double> (c_0.begin(), c_0.end() - 1);
		
		vector<double> next_state = eval_v_step(f_syst, c_i, t);

		syst_states.push_back(next_state);
	}

	return syst_states; 
}
