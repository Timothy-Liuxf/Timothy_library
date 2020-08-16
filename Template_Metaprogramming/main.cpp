#include <iostream>
#include "metaalgorithm.h"

using std::cout; 
using std::endl; 

int main()
{
	
	cout << Timothy::second_order_homogeneous_linear_recursive_sequence<5, 1, 2, 2, 3>::val << std::endl; 
	return 0; 
}
