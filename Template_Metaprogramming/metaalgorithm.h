//////////////////
//
// 模板元编程
//

#ifndef METAALGORITHM_H

#define METAALGORITHM_H

#include <Timothy_all.h>

__TIMOTHY_NAMESPACE_BEGIN

//////////////////
//
// 整数
//

template <typename _Ty, _Ty n>
struct meta_type
{
	static inline const _Ty val = n;
}; 

template <int n> using meta_int = meta_type<int, n>; 
template <signed char n> using meta_schar = meta_type<signed char, n>;
template <short n> using meta_short = meta_type<short, n>;
template <long n> using meta_long = meta_type<long, n>;
template <long long n> using meta_long_long = meta_type<long long, n>;
template <unsigned int n> using meta_uint = meta_type<unsigned int, n>;
template <unsigned char n> using meta_uchar = meta_type<unsigned char, n>;
template <unsigned short n> using meta_ushort = meta_type<unsigned short, n>;
template <unsigned long n> using meta_ulong = meta_type<unsigned long, n>;
template <unsigned long long n> using meta_ulong_long = meta_type<unsigned long long, n>; 

#ifdef	TIMOTHY_CXX20_SUPPORT		//如果支持CXX20

template <float n> using meta_float = meta_type<float, n>;
template <double n> using meta_double = meta_type<double, n>;
template <long double n> using meta_long_double = meta_type<long double, n>;

#endif 

//加法

template <typename _Meta_Ty1, typename _Meta_Ty2>
struct meta_add
{
	static inline const auto val = _Meta_Ty1::val + _Meta_Ty2::val; 
}; 

//减法

template <typename _Meta_Ty1, typename _Meta_Ty2>
struct meta_sub
{
	static inline const auto val = _Meta_Ty1::val - _Meta_Ty2::val;
}; 

//乘法

template <typename _Meta_Ty1, typename _Meta_Ty2>
struct meta_mul
{
	static inline const auto val = _Meta_Ty1::val * _Meta_Ty2::val;
};

//除法

template <typename _Meta_Ty1, typename _Meta_Ty2>
struct meta_div
{
	static inline const auto val = _Meta_Ty1::val / _Meta_Ty2::val;
};

//模除

template <typename _Meta_Ty1, typename _Meta_Ty2>
struct meta_mod
{
	static inline const auto val = _Meta_Ty1::val % _Meta_Ty2::val;
}; 

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
	static_assert(n >= m, "The \"n\" of the number of permutation must be no less than \"m\""); 
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
struct meta_sum
{
	static inline const unsigned int val = n + meta_sum<n - 1u>::val; 
}; 

template<>
struct meta_sum<0>
{
	static inline const unsigned int val = 0u; 
};

//////////////////
//
// 判断素数
//

template<unsigned int n>
struct is_prime
{
private: 

	template <unsigned int n, unsigned int m>
	struct NextN
	{
		static const inline unsigned int val = n % m ? n : 0u; 
	};

	template <unsigned int n, unsigned int m>
	struct NextM
	{
		static const inline unsigned int val = m * m <= n ? (m + 1u) : 0u; 
	};

	template <unsigned int n, unsigned int m>
	struct calculate
	{
		static inline const bool val = calculate<NextN<n, m>::val, NextM<n, m>::val>::val;
	}; 

	template <unsigned int m>
	struct calculate<0u, m>
	{
		static inline const bool val = false; 
	}; 

	template <unsigned int n>
	struct calculate<n, 0u>
	{
		static inline const bool val = true; 
	};

public: 

	static inline const bool val = calculate<n, 2u>::val;

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


__TIMOTHY_NAMESPACE_END

#endif	//#ifndef METAALGORITHM_H
