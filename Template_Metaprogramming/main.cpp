#include <iostream>
#include "metaalgorithm.hpp"
#include "BrainFuck.hpp"

using std::cout; 
using std::endl; 

int main()
{
	//Timothy::number_of_combination<99, 2>::val;
	auto out = Timothy::BrainFuck<128, 128>::Eval(std::cin, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
	auto outptr = out.GetArr();
	for (std::size_t i = 0u; i < out.GetLength(); ++i)
	{
		std::cout.put(out[i]);
	}
	std::cout.flush();
	return 0; 
}
