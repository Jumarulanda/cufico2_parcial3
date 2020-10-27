#include "gl_class.h"

double f(double (*)(double,double));
double glove(double,double);

int main(){

	std::cout << f(glove) << std::endl;

	return 0;
}

double f(double (*f_in)(double,double)){
	double a = 2, b = 3;
	double result = f_in(a,b);

	return result;	
}

double glove(double x, double y){
	gloved c_ins;

	double result = c_ins.g_fun(x,y);

	return result;
}
