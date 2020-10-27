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
  init_cond_eq_1 = {boundary_c[0],0,0};// vector {y, y', x} 
  init_cond_eq_2 = {0,1,0};// vector {y, y', x}
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
