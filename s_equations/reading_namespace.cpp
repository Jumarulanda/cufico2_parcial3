#include <iostream>
#include <vector>
#include "namespace_s_eq.cpp"
//#include "../rk_int/rk_int.h"


using namespace std;
using namespace namespace_s_eq;

vector <double> f(double);

int main()
{
  vector <double> (*pfunc)(double) = f; 
}

vector <double> f(double x)
{
  double px = -2/x;
  double qx = 2/pow(x,2);
  double rx = sin(log(x))/pow(x,2);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}
