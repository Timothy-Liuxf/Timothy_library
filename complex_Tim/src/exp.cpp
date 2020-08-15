#include "complex_Tim.h"
#include <iostream>
void main2()
{
	Timothy::complex<int> c(2, 6);
	std::cout << c << std::endl;
}
//
//#include <iostream>
//
//void Fun()
//{
//	Timothy::complex<int> c1(2, 3);
//	Timothy::complex<double> c2(1.5, 0);
//	Timothy::complex<int> c3 = static_cast<Timothy::complex<int>>(c2);	Timothy::complex<double> c9(2.1, 0);
//
//	std::cout << static_cast<Timothy::complex<int>>(9) + c1 << std::endl;
//	std::cout << c1 + 6.56;
//	c1 = 3.0;
//	std::cout << std::endl << "hhhhhhh" << c1 << std::endl;
//	c1 += 6;
//	std::cout << c1 << std::endl;
//	c1 -= 5;
//	std::cout << c1 << std::endl;
//	c1 *= 2;
//	std::cout << c1 << std::endl;
//	c1 *= Timothy::complex<double>(1, 5);
//	std::cout << c1 << std::endl;
//
//	c1 = 3;
//
//
//	c1 = Timothy::complex(-5, -89);
//
//
//	std::cout << c1--;
//	std::cout << c1 << std::endl;
//
//	Timothy::set_complex_format(Timothy::compl_fmt::std_math_format);
//
//	std::cout << c1 << std::endl;
//
//	Timothy::set_complex_format(Timothy::compl_fmt::engi_math_format);
//
//	std::cout << c1 << std::endl;
//}
