#include "condition_verifier.h"

// Three posible functions
double p(double x){ return pow(x,2);}
double q(double x){ return pow(sin(x),2);}
double r(double x){ return exp(x);}

int main()
{
    // Create a vector for storing the functions
    vector <double (*)(double)> funvec;
    funvec = {p,q,r};
        
    bool b = condition_verifier::check_conditions(funvec,-5,5);
    
    if (b)
    {
        cout << "Cumple las condiciones" << endl;
    }
    else
    {
        cout << "No cumple las condiciones" << endl;
    }
    return 0;
}