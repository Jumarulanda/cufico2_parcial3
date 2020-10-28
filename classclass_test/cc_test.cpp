#include "c2.h"

int main(){
	class_1 c1_instance;
	class_2 c2_instance;

	int (class_2::*) (int,int) *f_ptr = c2_instance.c2_function;


	/* c1_instance.eval_int_function(c2_instance.c2_function); */	

	return 0;
}

