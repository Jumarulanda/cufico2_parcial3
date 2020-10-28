#include <iostream>
#include <cmath>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

namespace rk_int{

	// Runge kutta integration 
	class rk{
		public:
		rk();
		vector<vector<double>> odint_rk4(vector<double (*)(double,vector<double>)>, vector<double>, double);	

		void set_tstep(double);

		private:
		float t_step;

		double rk4_step(double (*)(double,vector<double>),double,vector<double>,double);
		/* double rk6_step(double (double,vector<double>),double,vector<double>,double); */
		/* double rk8_step(double (double,vector<double>),double,vector<double>,double); */

		vector<double> eval_v_step(vector<double (*)(double,vector<double>)>, vector<double>, double);
		void print_tevol(vector<double>);
	};

}
