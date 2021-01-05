
#ifndef EXCEPTION_TIM_H

#define EXCEPTION_TIM_H

#include <Timothy_all.h>

#include <string>

__TIMOTHY_NAMESPACE_BEGIN

class t_exception		//异常类
{
private:
	std::string _str_excp;
public:
	t_exception() { _str_excp = "Timothy::t_exception"; }
	t_exception(const std::string& str_error) { _str_excp = str_error; }
	template <typename outstream>
	friend outstream& operator<<(outstream& out, const t_exception& _Val);	//输出异常信息
};

class divided_by_zero : public t_exception		//除数为0的异常
{
public:
	divided_by_zero() : t_exception("The divisor cannot be zero!") {}
};

class no_format : public t_exception		//输出格式值错误异常
{
public:
	no_format() : t_exception("No this output format!") {}
};

class input_error : public t_exception		//输出格式值错误异常
{
public:
	input_error() : t_exception("Input format error!") {}
};

class math_error : public t_exception
{
public:
	math_error() : t_exception("There are some operation not allowed in math!") {}
};

class out_range : public t_exception
{
public:
	out_range() : t_exception("Out of range!") {}
};

class empty_delegate : public t_exception
{
public:
	empty_delegate() : t_exception("Call empty delegate!") {}
};

class empty_collection : public t_exception
{
public:
	empty_collection(const std::string& collection = "collection") : 
		t_exception("The collection " + collection + " is empty!") {}
};

template <typename outstream>
inline outstream& operator<< (outstream& out, const t_exception& _Val)
{
	return out << _Val._str_excp;
}


__TIMOTHY_NAMESPACE_END

#endif
