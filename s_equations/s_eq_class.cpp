#include <iostream>
#include <vector>
#include <cmath>
#include "s_eq_class.h"


using namespace std;

s_diff_eq :: s_diff_eq(vector <double> cond, vector <double> (*f)(double))
//s_diff_eq :: s_diff_eq(vector <double> (*f)(double))
{
  boundary_c = cond;
  pfunc = f;
  init_cond_eq_1 = {boundary_c[0],0,boundary_c[2]};// vector {y(a), y'(a), a} 
  init_cond_eq_2 = {0,1,boundary_c[2]};// vector {y, y', x}
}

double s_diff_eq:: y_prime (double x, vector <double> vect)
{
  double dy = vect[1];
  return dy;
}
//this function is equivalent to  u' = p(x)u+q(x)y+r(x)
double s_diff_eq::y_dprime_1 (double x, vector <double> vect)
{
  vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
  double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
  return du;
}

//this function is equivalent to  u' = p(x)u+q(x)y
double s_diff_eq::y_dprime_2 (double x, vector <double> vect)
{
  vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
  double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
  return du;
}
/*
vector<vector<double>>  s_diff_eq::rk4_imp(void)
{
  rk_int :: rk rk_integrator;
  double t_step = 0.1;
  rk_integrator.set_tstep(t_step);
  vector<vector<double>> solutions;
  vector< double (*)(double,vector<double>)> ode_syst_1 = {*y_prime,*y_dprime_1};
  double t_end = 5.;
  solutions  = rk_integrator.odint_rk4(ode_syst_1,init_cond_eq_2, t_end);
  return solutions;
}
*/
