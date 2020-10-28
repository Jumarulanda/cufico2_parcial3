#include <cmath>
#include "../rk_int/rk_int.h"

using std::sin;
using std::log;
using std::pow;

double y1_d(double,vector<double>);
double u1_d(double,vector<double>);

int main(){
	rk_int :: rk rk_integrator;

	double t_step = 0.005;
	rk_integrator.set_tstep(t_step);

	vector<double> c0 = {1,0,1};

	vector<vector<double>> sols;

	vector<double (*)(double,vector<double>)> ode_syst = {*y1_d,*u1_d};	

	double t_end = 2.;
	sols = rk_integrator.odint_rk4(ode_syst, c0, t_end);

	return 0;
}

double y1_d(double x, vector<double> y1_u1){
	double u1 = y1_u1[1];

	return u1;
}

double u1_d(double x, vector<double> y1_u1){
	double u1 = y1_u1[1];
	double y1 = y1_u1[0];

	double y1_d_ret = -2.*u1/x + 2.*y1/pow(x,2) + sin(log(x))/pow(x,2);

	return y1_d_ret; 
}


