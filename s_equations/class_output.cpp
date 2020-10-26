#include <iostream>
#include <vector>
#include "s_eq_class.h"
#include "../rk_int/rk_int.h"

using namespace std;

vector <double> f(double);

int main()
{
  vector <double> v {1,2};
  s_diff_eq trying_class(v,f);
  
}

vector <double> f(double x)
{
  double px = -2/x;
  double qx = 2/pow(x,2);
  double rx = sin(log(x))/pow(x,2);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}
