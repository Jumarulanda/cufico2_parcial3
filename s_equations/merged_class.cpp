#include "merged_class.h"


vector<double> vec_sum(vector<double> vec, double sum){
	int vsize = vec.size();
	for (int i = 0; i < vsize; i++){
		vec[i] += sum;
	}

	return vec;	
}



merged_class::rk:: rk(vector <double> cond,vector <double> cond_x, vector <double> (*f)(double))

{ 
	float t_step = 0.1;
	boundary_c = cond;
	pfunc = f;
	init_cond_eq_1 = {boundary_c[0],0,cond_x[0]};// vector {y, y', x} 
	init_cond_eq_2 = {0,1,cond_x[0]};// vector {y, y', x}
}

// ############## Maryi#########################
//this function is equivalent to y' = u
double merged_class:: rk:: y_prime (double x, vector <double> vect)
{
  double dy = vect[1];
  return dy;
}
//this function is equivalent to  u' = p(x)u+q(x)y+r(x)
double merged_class:: rk::y_dprime_1 (double x, vector <double> vect)
{
  vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
  double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
  return du;
}

//this function is equivalent to  u' = p(x)u+q(x)y
double merged_class:: rk::y_dprime_2 (double x, vector <double> vect)
{
  vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
  double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
  return du;
}





// ############## Juan pa #########################


double merged_class :: rk::rk4_step(double (*f)(double,vector<double>)  , double y_i, vector<double> y_n, double t_n){
  
  double k1 =  f(t_n, y_n);
  double k2 =  f(t_n + t_step*0.5, vec_sum(y_n, k1*0.5));
  double k3 =  f(t_n + t_step*0.5, vec_sum(y_n, k2*0.5));
  double k4 =  f(t_n + t_step    , vec_sum(y_n, k3));

  return y_i + t_step*(k1 + 2.*k2 + 2.*k3 + k4)/6.; 
}


vector<double> merged_class :: rk::eval_v_step(vector<double (*)(double,vector<double>)> f_syst, vector<double> y_n, double t_n){	
	vector<double> y_np1;

	int vsize = f_syst.size();
	for (int i=0; i < vsize; i++){
	  y_np1.push_back(rk4_step(f_syst[i], y_n[i], y_n, t_n));
	}	

	y_np1.push_back(t_n);
	return y_np1;
}

vector<vector<double>> merged_class :: rk::odint_rk4(vector<double (*)(double,vector<double>)> f_syst, vector<double> c_0, double t_f){

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

void merged_class :: rk::set_tstep(double n_tstep){
	t_step = n_tstep;	
	cout << "Time step set to: " << t_step << endl;
}

void merged_class :: rk::print_tevol(vector<double> c_n){
	int vsize = c_n.size();
	for (int i = 0; i < (vsize - 1); i++){
		cout << c_n[i] << ",";
	}	
	cout << c_n.back() << endl;
}

vector<vector<double>> merged_class :: rk::computing_eq_1(void)
{
  vector<vector<double>> solutions;
  double (*Ptr_dy)(double, vector <double> )= &y_prime;
  double (*Ptr_ddy_1)(double, vector <double> )= &y_dprime_1;
  vector<double (*)(double,vector<double>)> ode_syst_1 = {Ptr_dy,Ptr_ddy_1};
  double t_end = boundary_c[1];
  solutions = odint_rk4(ode_syst_1,init_cond_eq_1, t_end);
  return solutions;
}


