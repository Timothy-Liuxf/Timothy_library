#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "complex_Tim.h"
#include <complex>
#include <iostream>
using namespace std;
void main2();
namespace ty = Timothy;
int main()
{

	try
	{
		//ty::set_complex_format(ty::compl_fmt::magpi_math_format);
		Timothy::complex<double> c1;
		Timothy::complex<double> c2;
		Timothy::cpl_cal::clog(c1);
		do
		{
			std::cout << "c1: " << c1 << std::endl;
			std::cout << "c2: " << c2 << std::endl;
		} while (std::cin >> c1 >> c2);
	}
	catch (Timothy::t_exception e)
	{
		std::cout << e << std::endl;
	}
	return 0;
}
