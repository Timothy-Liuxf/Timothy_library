
#include <iostream>
#include "delegate_Tim.h"

int Func1(void)
{
	int k = 1;
	std::cout << "1: " << k << std::endl;
	return k + 1;
}


int Func2(void)
{
	int k = 2;
	std::cout << "2: " << k << std::endl;
	return k + 2;
}


int Func3(void)
{
	int k = 3;
	std::cout << "3: " << k << std::endl;
	return k + 3;
}

int Func5(int cc)
{
	int k = 5;
	std::cout << "5: " << k << std::endl;
	return k + 5;
}


using std::cout; 
using std::endl; 
int main()
{
	try
	{
		Timothy::delegate<int> d; 
		d.allocate(100);
		d.reset(3, Func1, Func2, Func3); 
		
		d(); 
		cout << "==================" << endl; 
		d *= 3; 
		d(); 
	}
	catch (Timothy::t_exception e)
	{
		cout << e << endl; 
	}

	return 0;
}
