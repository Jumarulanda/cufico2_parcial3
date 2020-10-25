
#include <iostream>
#include <vector>

//using namespace std;

class s_diff_eq

{
  
 public:
  s_diff_eq(std :: vector <double>,std:: vector <double> (*)(double));
  std::vector <double> boundary_c;
  //void printer(double);

  //The following defenitions should be private, then we have to use friend functions.
  double y_prime (double, std::vector <double> );
  double y_dprime_1 (double ,std:: vector <double>);
  double y_dprime_2 (double ,std:: vector <double>);
  std::vector<double> init_cond_eq_1;
  std::vector<double> init_cond_eq_2;
 private:
   std::vector <double> (*pfunc)(double);
};
