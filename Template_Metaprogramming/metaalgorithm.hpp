//////////////////
//
// 模板元编程
//

#ifndef METAALGORITHM_H

#define METAALGORITHM_H

#include <Timothy_all.h>
#include <cstdint>

__TIMOTHY_NAMESPACE_BEGIN

//////////////////
//
// 计算阶乘
//

template <unsigned int n>
struct factorial
{
	static inline const unsigned long long val = n * factorial<n - 1>::val; 
}; 

template <>
struct factorial<0>
{
	static inline const unsigned long long val = 1ull; 
}; 

//////////////////
//
// 计算双阶乘
//

template <unsigned int n>
struct double_factorial
{
	static inline const unsigned long long val = n * double_factorial<n - 2u>::val;
}; 

template <>
struct double_factorial<1>
{
	static inline const unsigned long long val = 1ull; 
};

template <>
struct double_factorial<0>
{
	static inline const unsigned long long val = 1ull;
};

///////////////////
//
// 计算排列数
//

template <unsigned int n, unsigned int m>
struct number_of_permutation
{
	static_assert(n >= m, "The \"n\" of the number of permutation must be no less than \"m\"."); 
	static inline const unsigned long long val = n * number_of_permutation<n - 1u, m - 1u>::val; 
}; 

template <unsigned int n>
struct number_of_permutation<n, 0>
{
	static inline const unsigned long long val = 1ull; 
}; 

///////////////////
//
// 计算组合数
//

template <unsigned int n, unsigned int m>
struct number_of_combination
{
	static_assert(n >= m, "The \"n\" of the number of combination must be no less than \"m\"");
	static inline const unsigned long long val = m < n - m ? number_of_permutation<n, m>::val / factorial<m>::val : number_of_permutation<n, n - m>::val / factorial<n - m>::val;
};

//////////////////
//
// 求1~n的和
//

template<unsigned int n>
struct meta_continuous_sum
{
	static inline const unsigned int val = n + meta_continuous_sum<n - 1u>::val; 
}; 

template<>
struct meta_continuous_sum<0>
{
	static inline const unsigned int val = 0u; 
};

///////////////////
//
// 求若干个数的和
//

template <typename _Ty, _Ty num1, _Ty... nums>
struct meta_sum
{
	static inline const _Ty val = num1 + meta_sum<_Ty, nums...>::val; 
};

template <typename _Ty, _Ty num1>
struct meta_sum<_Ty, num1>
{
	static inline const _Ty val = num1; 
};

//////////////////
//
// 判断素数
//

template <unsigned int n, unsigned int m>
struct Test_Prime_NextN
{
	static const inline unsigned int val = n % m ? n : 0u;
};

template <unsigned int n, unsigned int m>
struct Test_Prime_NextM
{
	static const inline unsigned int val = m * m <= n ? (m + 1u) : 0u;
};

template <unsigned int n, unsigned int m>
struct Test_Prime_calculate
{
	static inline const bool val = Test_Prime_calculate<Test_Prime_NextN<n, m>::val, Test_Prime_NextM<n, m>::val>::val;
};

template <unsigned int m>
struct Test_Prime_calculate<0u, m>
{
	static inline const bool val = false;
};

template <unsigned int n>
struct Test_Prime_calculate<n, 0u>
{
	static inline const bool val = true;
};

template<unsigned int n>
struct is_prime
{
public: 

	static inline const bool val = Test_Prime_calculate<n, 2u>::val;

}; 


template<>
struct is_prime<2>
{
	static inline const bool val = true;
};


template<>
struct is_prime<1>
{
	static inline const bool val = false; 
};

template<>
struct is_prime<0>
{
	static inline const bool val = false;
};

//////////////////////
//
//
// 判断合数

template <unsigned int n>
struct is_composite
{
	static inline const bool val = !is_prime<n>::val; 
}; 
 
template <>
struct is_composite<1>
{
	static inline const bool val = false;
};

template <>
struct is_composite<0>
{
	static inline const bool val = false;
}; 

//////////////////
//
// 计算2阶齐次线性递推数列的第n项
// f(k) = para1 * f(k - 1) + para2 * f(k - 2) + ... + paran * f(k - n), 
// f(0) = initial0, f(1) = initial1
//

template <unsigned int n, long long initial0, long long initial1, long long para1, long long para2>
struct second_order_homogeneous_linear_recursive_sequence
{
	static inline const long long val
		= para1 * second_order_homogeneous_linear_recursive_sequence<n - 1, initial0, initial1, para1, para2>::val
		+ para2 * second_order_homogeneous_linear_recursive_sequence<n - 2, initial0, initial1, para1, para2>::val; 
};

template <long long initial0, long long initial1, long long para1, long long para2>
struct second_order_homogeneous_linear_recursive_sequence<0, initial0, initial1, para1, para2>
{
	static inline const long long val = initial0; 
};

template <long long initial0, long long initial1, long long para1, long long para2>
struct second_order_homogeneous_linear_recursive_sequence<1, initial0, initial1, para1, para2>
{
	static inline const long long val = initial1;
};

//斐波那契

template <unsigned int n> using fibonacci = second_order_homogeneous_linear_recursive_sequence<n, 0, 1, 1, 1>; 

__TIMOTHY_NAMESPACE_END

#endif	//#ifndef METAALGORITHM_H
