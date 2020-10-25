#include "condition_verifier.h"

bool condition_verifier::is_continuous(double (*f)(double),double start, double end)
{
    bool continuous = true;
    
    vector<double> ifun;
    int num = 10000;
    double delta = (end - start) / num;
    
    for (double x = start; x < end; x += delta)
        {
            if (isinf(f(x)))
            {
                continuous = false;
                break;
            }
            if (isnan(f(x)))
            {
                continuous = false;
                break;
            }
        
            ifun.push_back(1/f(x));
        }
    
    for (int i = 1; i < ifun.size() ; i++)
    {
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

    int num = 10000;
    bool define_positive = true;
    double delta = (end - start) / num;
    
    for (double x = start; x < end; x += delta)
    {
        if (f(x) < 0)
        {
            define_positive = false;
        }
    }
    
    return define_positive;
}

bool condition_verifier::check_conditions(vector<double (*)(double)> funvec, double start, double end)
{
    
    bool bp = is_continuous(funvec[0],start,end);
    bool bq = is_continuous(funvec[1],start,end);
    bool br = is_continuous(funvec[2],start,end);
    
    bool b = is_defined_positive(funvec[1],start,end);
    
    /*
    cout << bp << endl;
    cout << bq << endl;
    cout << br << endl;
    cout << b << endl;
    */
    
    return bp && bq && br && b;
}





