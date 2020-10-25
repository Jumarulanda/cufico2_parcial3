#include "tfunc.h"

tfunc::tfunc(int (*infunc)(int,int)){
	// set function pointer
	px = infunc;
	std::cout << "Function pointer set" << std::endl;	
}

int tfunc::input_func(int a, int b){
		return px(a,b);
}
