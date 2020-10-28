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


double rk_int :: rk::rk4_step(double f (double,vector<double>), double y_i, vector<double> y_n, double t_n){
	double k1 = t_step * f(t_n, y_n);
	double k2 = t_step * f(t_n + t_step*0.5, vec_sum(y_n, k1*0.5));
	double k3 = t_step * f(t_n + t_step*0.5, vec_sum(y_n, k2*0.5));
	double k4 = t_step * f(t_n + t_step    , vec_sum(y_n, k3));

	return y_i + (k1 + 2.*k2 + 2.*k3 + k4)/6.; 
}

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

	for (double t = c_0.back()+t_step; t <= t_f+t_step; t += t_step){
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
