#include <iostream>
#include <vector>
#include <cmath>
#include "s_eq_class.h"

using namespace std;

vector <double> f(double);


int main()
{
  vector <double> v {20,1};
  s_diff_eq trying_class(v,f);
  cout << "checking..." <<endl;
  for (double i:trying_class.init_cond_eq_2)
    cout << i << endl;
  return 0;
}

vector <double> f(double x)
{
  double px = -2/x;
  double qx = 2/pow(x,2);
  double rx = sin(log(x))/pow(x,2);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}