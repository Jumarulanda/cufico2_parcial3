#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


vector <double> f(double);
vector <double> s_eq_1(vector <double> (*f)(double),double);
vector <double> s_eq_2(vector <double> (*f)(double),double);


int main()
{
  vector <double> vect = f(1);
   for (double x : vect) 
        cout << x << " "; 
   cout << "\n";
   vector <double> vect_1 = s_eq_1(f,1);
   for (double x : vect_1) 
        cout << x << " "; 
  return 0;
}


/* 
This function takes values of a second order differential equation given by the form: 
y'' = p(x)y'+q(x)y+r(x)
*/
vector <double> f(double x)
{
  double px = -2/x;
  double qx = 2/pow(x,2);
  double rx = sin(log(x))/pow(x,2);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}

//Obtaining the first differential equation for the approximation
vector <double> s_eq_1(vector <double> (*f)(double),double x)
{
  vector <double> vect = f(x);
  vector <double> vect_1;
  vect_1.emplace_back(vect[0]);
  vect_1.emplace_back(vect[1]);
  vect_1.emplace_back(vect[2]);
  return vect_1;
}

//Obtaining the second differential equation for the approximation
vector <double> s_eq_2(vector <double> (*f)(double),double x)
{
  vector <double> vect = f(x);
  vector <double> vect_1;
  vect_1.emplace_back(vect[0]);
  vect_1.emplace_back(vect[1]);
  return vect_1;
}

double f_eq(double x, vector <double> vect)
{
  double y_prim = vect[1];
  return y_prim;
}


double f_eq_1(double x, vector <double> vect)
{
  double y_prim = vect[1];
  
  return y_prim;
}
