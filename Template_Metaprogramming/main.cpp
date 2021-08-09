
#include "metaalgorithm.hpp"
#include "BrainFuck.hpp"
#include "sort.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>

using std::cout; 
using std::endl;

template <typename T, T first, T... vals>
void print_seq(Timothy::sequence<T, first, vals...> s)
{
	constexpr T arr[]{ first, vals... };
	
	for (auto i : arr)
	{
		cout << i << " ";
	}
	endl(cout);
}

template <typename T>
void print_seq([[maybe_unused]] Timothy::sequence<T> s)
{
	endl(cout);
}

int main()
{
	//cout << Timothy::is_prime<4>::val << endl;
	//
	////Timothy::number_of_combination<99, 2>::val;
	//auto out = Timothy::BrainFuck<128, 128>::Eval(std::cin, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
	//auto outptr = out.GetArr();
	//for (std::size_t i = 0u; i < out.GetLength(); ++i)
	//{
	//	std::cout.put(out[i]);
	//}
	//std::cout.flush();

	Timothy::choose_sort<Timothy::sequence<int, 1, 9, -3>>::type t;
	print_seq(t);
	return 0;
}
