#include <iostream>
#include <vector>
#include <iomanip>
#include "s_eq_class.h"
#include "../rk_int/rk_int.h"

using namespace std;
//using namespace namespace_s_eq;

vector <double> f(double);
double glove_1(double,  vector <double> );
double glove_2(double,  vector <double> );
double glove_3(double,  vector <double> );
//vector<vector<double>> joint_sol(vector<vector<double>>);
void joint_sol(vector<vector<double>>solution_1,vector<vector<double>>solution_2,double t_step);
vector <double> boundary {1,2,1,2}; //vector with componentes [y(a),y(b),a,b]
s_diff_eq c_ins(boundary,f);


int main()
{
  // vector <double> (*pfunc)(double) = f;
  rk_int :: rk rk_integrator;
  double t_step = 0.1;
  rk_integrator.set_tstep(t_step);
  vector<vector<double>> solutions_1;
  vector<vector<double>> solutions_2;
 
  vector< double (*)(double,vector<double>)> ode_syst_1 = {*glove_1,*glove_2};
  vector< double (*)(double,vector<double>)> ode_syst_2 = {*glove_1,*glove_3};
  double t_end = boundary[3];
  solutions_1  = rk_integrator.odint_rk4(ode_syst_1,c_ins.init_cond_eq_1, t_end);
  cout << "equation 2" <<endl;
  solutions_2  = rk_integrator.odint_rk4(ode_syst_1,c_ins.init_cond_eq_2, t_end);
  double a = solutions_2[1][1];
  cout << "printing: " << a << endl;
  joint_sol(solutions_1,solutions_2,0.1);
}

vector <double> f(double x)
{
  double px = -2./x;
  double qx = 2./pow(x,2.);
  double rx = sin(log(x))/pow(x,2.);
  vector <double> eq_values {px,qx,rx};
  return eq_values;
}

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

//vector<vector<double>> joint_sol(vector<vector<double>>solution_1,vector<vector<double>>solution_2,double t_step)
void joint_sol(vector<vector<double>>solution_1,vector<vector<double>>solution_2,double t_step)
{ int N = (boundary[3]-boundary[2])/t_step;
  cout << "N_value: " << N << endl;
  double w20 =  (boundary[3] - solution_1[N][0])/solution_2[N][0];
  //vector<vector<double>> W;
  double W1;
  double W2;
  double x;
  for (int i=0; i<=N ; i++)
    {
      W1 = solution_1[i][0]+w20*solution_2[i][0];
      W2 = solution_1[i][1]+w20*solution_2[i][1];
      x =  solution_1[i][2];
      cout << W1 << "," << W2 << "," << x <<endl;
    }
}
