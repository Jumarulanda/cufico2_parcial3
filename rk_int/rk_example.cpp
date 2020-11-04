#include <cmath>
#include "rk_int.h"

using std::sin;

double theta_dot(double, vector<double>);
double omega_dot(double, vector<double>);

int main(){
	// create integratonr instance	
	rk_int :: rk rk_integrator;

	// set a time step and update it into integrator instance
	double t_step = 0.1;
	rk_integrator.set_tstep(t_step);

	// set a initial state vector, time goes ALWAYS last. In this case, order is {theta_0,omega_0,t_0}
	vector<double> c0 = {0,1,0};

	// create a vector of double vectors to store solutions
	vector<vector<double>> solutions;
	
	// create a vector of functions containing the initial conditions in the same order as the entries of the initial condition vector (excluding time)
	vector<double (*)(double,vector<double>)> ode_syst = {*theta_dot,*omega_dot};

	// set a final integration time and run integrating function
	double t_end = 5.0;
	solutions = rk_integrator.odint_rk4(ode_syst, c0, t_end);
	for (vector <double> i: solutions)
	  {
	    for (double j:i)
	      cout << j<<",";
	    cout << '\n';
	  }

	return 0;
}

// ---------------- ODE test system -------------

double theta_dot(double t, vector<double> theta_omega){
	double omega = theta_omega[1];

	return omega;	
}

double omega_dot(double t, vector<double> theta_omega){
	double p1 = -0.25*theta_omega[1];   
	double p2 = -5.*sin(theta_omega[0]);

	return p1 + p2;
}
