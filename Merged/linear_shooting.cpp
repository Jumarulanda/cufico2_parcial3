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

using namespace std;

int main()
{       
    // Verifying conditions
    
    auto p = [](double x){return df::f(x)[0];};
    auto q = [](double x){return df::f(x)[1];};
    auto r = [](double x){return df::f(x)[2];};
    
    vector <double (*)(double)> F;
    F = {p,q,r};
    bool B = tools::check_conditions(F,df::boundary[2],df::boundary[3]);
    
    if (not(B))
    {
        cout << "Warning: No se satisfacen las condiciones establecidas para poder usar el Linear Shooting de modo que las soluciones pueden estar incorrectas o inexactas"<< endl;
    }
    
    // Time step
    double t_step = 0.01;
    
    // Instance the integrator
    rk_int :: rk rk_integrator;        
    rk_integrator.set_tstep(t_step);
    
    // For storing the solutions
    vector<vector<double>> solutions_1;
    vector<vector<double>> solutions_2;
    
    // Defining the two system of differential equations
    vector< double (*)(double,vector<double>)> ode_syst_1 = {*df::glove_1,*df::glove_2};
    vector< double (*)(double,vector<double>)> ode_syst_2 = {*df::glove_1,*df::glove_3};
    
    // Calculating the solutions
    double t_end = df::boundary[3];
    solutions_1  = rk_integrator.odint_rk4(ode_syst_1,df::c_ins.init_cond_eq_1, t_end);
    solutions_2  = rk_integrator.odint_rk4(ode_syst_2,df::c_ins.init_cond_eq_2, t_end);
    
    ofstream file ("diff_sol.txt"); // File for storing solutions
    
    // Joint and write solutions
    tools::joint_sol(solutions_1, solutions_2, t_step, df::boundary, &file);
    
    return 0;
}


