#include <iostream>
#include <vector>
#include "s_eq_class.h"
#include "../rk_int/rk_int.h"

using namespace std;

vector <double> f(double);

int main()
{
  rk_int :: rk rk_integrator;
  //rk_int rk_integrator();
  vector <double> boundary {1,2}; //boundary conditions 
  s_diff_eq trying_class(boundary,f); //initializing class for equations separation.
  //s_diff_eq* Ptr_sep_eq; 
  //Ptr_sep_eq->y_prime;
  
  double t_step = 0.1;
  vector<vector<double>> solutions;
  double (s_diff_eq::*Ptr_dy)(double, vector <double> )= &s_diff_eq::y_prime;
  double (s_diff_eq::*Ptr_ddy_1)(double, vector <double> )=  &s_diff_eq::y_dprime_1;
  //dy = trying_class.y_prime;
  vector<double (*)(double,vector<double>)> ode_syst_1 = {trying_class.*Ptr_dy,trying_class.*Ptr_ddy_1};
  double t_end = boundary[1];
  solutions  = rk_integrator.odint_rk4(ode_syst_1,trying_class.init_cond_eq_1, t_end); 
  
  
 
  
  
}

vector <double> f(double x)
{
  double px = -2/x;
  double qx = 2/pow(x,2);
  double rx = sin(log(x))/pow(x,2);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}
