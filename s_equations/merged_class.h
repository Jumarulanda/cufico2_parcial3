#include <iostream>
#include <cmath>
#include <vector>


using std::vector;
using std::cout;
using std::endl;


namespace merged_class{

	// Runge kutta integration 
	class rk{


	public:
	  rk( vector <double>,vector <double>,vector <double> (*)(double));
	  vector <double> boundary_c;
	  //void printer(double);

	  //The following defenitions should be private, then we have to use friend functions.
	  double y_prime (double, vector <double> );
	  double y_dprime_1 (double ,vector <double>);
	  double y_dprime_2 (double , vector <double>);
	  std::vector<double> init_cond_eq_1;
	  std::vector<double> init_cond_eq_2;

	  
	  vector<vector<double>> odint_rk4(vector<double (*)(double,vector<double>)>, vector<double>, double);
	  void set_tstep(double);
	  vector<vector<double>> computing_eq_1(void);
	private:
	  float t_step;
	  std::vector <double> (*pfunc)(double);
	  double rk4_step(double (*)(double,vector<double>) ,double,vector<double>,double);
	  vector<double> eval_v_step(vector<double (*)(double,vector<double>)>, vector<double>, double);
	  void print_tevol(vector<double>);

	};

}
