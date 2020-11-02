#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

namespace tools
{
    bool is_continuous( double (*)(double),double,double);
    bool is_defined_positive(double (*)(double),double,double);
    bool check_conditions(vector<double (*)(double)>,double,double);
    void joint_sol(vector<vector<double>>, vector<vector<double>>, double, vector<double>, ofstream(*));
}

class s_diff_eq
{
public:
    s_diff_eq(vector <double>,vector <double> (*)(double));
    vector<double> boundary_c;

    double y_prime (double, vector <double> );
    double y_dprime_1 (double ,vector <double>);
    double y_dprime_2 (double ,vector <double>);
    vector<double> init_cond_eq_1;
    vector<double> init_cond_eq_2;
 
private:
    vector <double> (*pfunc)(double);
};

namespace rk_int
{
    class rk{
        public:
        
            rk();
            vector<vector<double>> odint_rk4(vector<double (*) (double,vector<double>)>, vector<double>, double);	
            void set_tstep(double);

		private:
        
            float t_step;
            double rk4_step(double (*)(double,vector<double>) ,double,vector<double>,double);
            vector<double> eval_v_step(vector<double (*)(double,vector<double>)>, vector<double>, double);
            void print_tevol(vector<double>);
	};
}


