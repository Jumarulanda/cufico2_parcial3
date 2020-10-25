#include "condition_verifier.h"

bool condition_verifier::is_continuous(double (*f)(double),double start, double end)
{
    // Verify the continuity of f within the interval [start,end]
    
    bool continuous = true;                 // f is considered continuous a priori
     
    vector<double> ifun;                    // Vector for storing the values of 1/f(x)
    int points = 10000;                     // Number of points used for testing continuity
    double delta = (end - start) / points;  // Step size
    
    for (double x = start; x < end; x += delta)
        {
            if (isinf(f(x)))
            {
                // If there is a inf value, f is not continuous
                continuous = false;
                break;
            }
            if (isnan(f(x)))
            {
                // If there is nan value, f is not continuous
                continuous = false;
                break;
            }
            // Fill a vector with the values of the function^-1
        
            ifun.push_back(1/f(x));
        }
    
    for (int i = 1; i < ifun.size() ; i++)
    {
        // If there is a change of sign in 1/f(x_o) there is a discontinuity of f(x) in x_o
        if ( abs(ifun[i]) < 50 &&  ifun[i] * ifun[i-1] < 0)
        {
            continuous = false;
            break;
        }
    }
    
    return continuous;
}

bool condition_verifier::is_defined_positive(double (*f)(double),double start, double end)
{

    int points = 10000;                     // Number of points used for testing positiveness
    bool define_positive = true;            // f is considered positive a priori
    double delta = (end - start) / points;  // Step size 
    
    for (double x = start; x < end; x += delta)
    {
        if (f(x) < 0)
        {
            // If there is a negative value within the interval is automatically not positive defined.
            define_positive = false;
        }
    }
    
    return define_positive;
}

bool condition_verifier::check_conditions(vector<double (*)(double)> funvec, double start, double end)
{
    // The input is an vector of three functions: {p(x),q(x),r(x)} and two numbers defining the interval [start,end]
    // The conditions for the linear shooting are the continuity of p(x),q(x),r(x) and q(x) must be positive defined.
    
    bool bp = is_continuous(funvec[0],start,end);  // Is p(x) continuous witih [start,end] ?
    bool bq = is_continuous(funvec[1],start,end);  // Is q(x) continuous witih [start,end] ?
    bool br = is_continuous(funvec[2],start,end);  // Is r(x) continuous witih [start,end] ?
    
    bool b = is_defined_positive(funvec[1],start,end);  // Is q(x) defined positive witih [start,end] ? 
    
    return bp && bq && br && b; // If all the conditions are satisfied, returns True, otherwise False
}





