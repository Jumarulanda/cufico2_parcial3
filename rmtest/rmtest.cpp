#include "tfunc.h"

int test_func(int,int);

int main(){

	tfunc class_instance(test_func);

	std::cout << class_instance.input_func(3,2) << std::endl;

	return 0;
}

int test_func(int a, int b){
		return a*b;
}
