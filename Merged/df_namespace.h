#include "merged_classes.h"

namespace df
{

    //~~~~ Modifiable part of the code ~~~~//
    
    vector<double> f(double x) //Function to integrate
    {
        double px = -2./x;
        double qx = 2./pow(x,2.);
        double rx = sin(log(x))/pow(x,2.);
        vector <double> eq_values {px,qx,rx};
        return eq_values;
    }
    
    // Boundary conditions [y(a),y(b),a,b]
    vector<double> boundary {1,2,1,2}; 

    //~~~~ Glove Functions ~~~~//

    s_diff_eq c_ins(boundary,f);  // Instance the separator

    double glove_1(double x,  vector <double> y)
    { 
        double result = c_ins.y_prime(x,y);
        return result;
    }
    
    double glove_2(double x,  vector <double> y)
    {
        double result = c_ins.y_dprime_1(x,y);
        return result;
    }
    
    double glove_3(double x,  vector <double> y)
    {
    double result = c_ins.y_dprime_2(x,y);
    return result;
    }
}