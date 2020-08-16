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
// 基本数据类型
//

template <typename _Ty, _Ty n>
struct meta_type
{
	static inline const _Ty val = n;
}; 

template <int n> using meta_int = meta_type<int, n>; 
template <signed char n> using meta_schar = meta_type<signed char, n>;
template <wchar_t n> using meta_wchar = meta_type<wchar_t, n>; 
template <short n> using meta_short = meta_type<short, n>;
template <long n> using meta_long = meta_type<long, n>;
template <long long n> using meta_long_long = meta_type<long long, n>;
template <unsigned int n> using meta_uint = meta_type<unsigned int, n>;
template <unsigned char n> using meta_uchar = meta_type<unsigned char, n>;
template <unsigned short n> using meta_ushort = meta_type<unsigned short, n>;
template <unsigned long n> using meta_ulong = meta_type<unsigned long, n>;
template <unsigned long long n> using meta_ulong_long = meta_type<unsigned long long, n>; 

template <int8_t n> using meta_int8 = meta_type<int8_t, n>; 
template <int16_t n> using meta_int16 = meta_type<int16_t, n>;
template <int32_t n> using meta_int32 = meta_type<int32_t, n>;
template <int64_t n> using meta_int64 = meta_type<int64_t, n>;
template <uint8_t n> using meta_uint8 = meta_type<uint8_t, n>;
template <uint16_t n> using meta_uint16 = meta_type<uint16_t, n>;
template <uint32_t n> using meta_uint32 = meta_type<uint32_t, n>;
template <uint64_t n> using meta_uint64 = meta_type<uint64_t, n>;

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

///////////////////
//
// 求若干个数的平均值
//

template<typename _Ty, typename _ResTy, _Ty...  nums>
struct meta_average
{
private: 

	struct result
	{
		_Ty sum; 
		unsigned int times; 
		constexpr result(_Ty sum, unsigned int times) : sum(sum), times(times) {}
		constexpr result(const result& r) : sum(r.sum), times(r.times) {}
	};

	template <unsigned int times, _Ty num1, _Ty... nums>
	struct calculate
	{
		static inline const result val = result(num1 + calculate<times + 1, nums...>::val.sum, calculate<times + 1, nums...>::val.times); 
	};

	template <unsigned int times, _Ty num1>
	struct calculate<times, num1>
	{
		static inline const result val = result(num1, times); 
	};

public: 
	static inline const _ResTy val = static_cast<_ResTy>(calculate<1, nums...>::val.sum) / static_cast<_ResTy>(calculate<1, nums...>::val.times);
};

template<typename _Ty, typename _ResTy>
struct meta_average<_Ty, _ResTy>
{
	static inline const _Ty val = static_cast<_ResTy>(0); 
};

template <typename _Ty, _Ty...  nums>
using meta_auto_average = meta_average<_Ty, _Ty, nums...>; 

/////////////////
//
// 求from~to阶乘的和
//

template <unsigned int from, unsigned int to>
struct meta_factorial_sum
{
	static_assert(from <= to, "The start number must be no greater than the end number."); 

private:

	struct result
	{
		unsigned long long sum; 
		unsigned long long fac; 
		constexpr result(unsigned long long sum, unsigned long long fac) : sum(sum), fac(fac) {}
		constexpr result(const result& r) : sum(r.sum), fac(r.fac) {}
	};

	template <unsigned int from, unsigned int to>
	struct calculate
	{
		static inline const result val = 
			result(calculate<from, to - 1u>::val.fac * to + calculate<from, to - 1u>::val.sum, calculate<from, to - 1u>::val.fac * to);
	};

	template <unsigned int end>
	struct calculate<end, end>
	{
		static inline const result val = result(factorial<from>::val, factorial<from>::val);
	};

public: 
	static inline const unsigned long long val = calculate<from, to>::val.sum; 
};

template <unsigned int end> using meta_factorial_sum_from_zero = meta_factorial_sum<0, end>; 
template <unsigned int end> using meta_factorial_sum_from_one = meta_factorial_sum<1, end>;

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
