#include <iostream>
#include <cmath>

class tfunc{
	public:
	tfunc(int (*)(int,int));
	int input_func(int,int);
	
	private:
	int (*px)(int,int);
};
