#include <iostream>
#include <cmath>
#include <vector>

using std::vector;

namespace rk_int{

	// Runge kutta integration 
	class rk{
		public:
		rk();
		vector<vector<double>> odint_rk4(vector<double (*)(double,double)>, vector<double>, double);		

		private:
		float t_step;

		double rk4_step(double (double,double),double,double);
		vector<double> eval_v_step(vector<double (*)(double,double)>, vector<double>, double);
	};

}
