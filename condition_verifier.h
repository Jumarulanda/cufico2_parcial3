#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace condition_verifier
{
    bool is_continuous( double (*)(double),double,double);
    bool is_defined_positive(double (*)(double),double,double);
    bool check_conditions(vector<double (*)(double)>,double,double);
}