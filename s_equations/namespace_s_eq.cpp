#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

namespace namespace_s_eq
{
  vector <double> (*pfunc)(double);

  double  y_prime (double x, vector <double> vect)
  {
    double dy = vect[1];
    return dy;
  }
  //this function is equivalent to  u' = p(x)u+q(x)y+r(x)
  double y_dprime_1 (double x, vector <double> vect)
  {
    vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
    double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
    return du;
  }

  //this function is equivalent to  u' = p(x)u+q(x)y
  double y_dprime_2 (double x, vector <double> vect)
  {
    vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
    double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
    return du;
    }
 
}
