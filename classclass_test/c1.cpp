#include "c1.h"

class_1::class_1(){}

void class_1::eval_int_function(int (*f)(int,int)){
	int a = 3;
	int b = 2;

	int eval = f(a,b);

	std::cout << eval << std::endl;
}
