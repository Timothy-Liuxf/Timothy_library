
#ifndef DELEGATE_TIM_H

#define DELEGATE_TIM_H

#include <cstdarg>
#include <typeinfo>
#include <exception_Tim.h>
#include <set>
#include <limits>

#ifdef _DEBUG

#include <iostream>
using std::cout; 
using std::endl; 

#endif

__TIMOTHY_NAMESPACE_BEGIN

template <typename _Rtn, typename..._arg>											//返回值类型为_Rtn，参数类型为_arg的委托，如果参数类型为void，则忽略此模板参数
class delegate
{
public:
	typedef _Rtn(*FUNPTR)(_arg...);
	constexpr static inline unsigned int npos = std::numeric_limits<unsigned int>::max();	//常量，表示找不到位置

	//构造函数

	delegate() : _fp(new FUNPTR[1]), _func_num(0), _capacity(1) {}
	delegate(FUNPTR func) : _fp(new FUNPTR[1]), _func_num(1), _capacity(1) { _fp[0] = func; }		//单播委托
	delegate(unsigned int _num, ...);									//多播委托，委托的函数个数为_num
	delegate(unsigned int _cap) : _fp(new FUNPTR[_cap == 0 ? (++_cap) : _cap]), 
		_func_num(0), _capacity(_cap) {}											//预先给委托分配_cap个（至少1个）函数指针的空间
	delegate(FUNPTR* _First, FUNPTR* _Last);										//多播委托，将函数指针数组_First到_Last全部委托（包括_First，不包括_Last）
	delegate(const delegate& _srcdelg);
	delegate(delegate&& _srcdelg) noexcept
	{
		_capacity = _func_num = _srcdelg._func_num;
		_fp = _srcdelg._fp;
		_srcdelg._fp = nullptr;
		_srcdelg._func_num = 0;
	}

	//使用委托

	void reset() { _func_num = 0; }											//重设委托，使其不委托任何函数
	void __cdecl reset(unsigned int _num, ...);								//重设委托，使其委托_num个函数，_num后必须有且只有_num个函数指针作为参数
	void clear();															//重设委托，并清空内存空间
	void clear(FUNPTR _newfunc);											//重设委托，清空内存空间，并使其委托1个函数
	void __cdecl clear(unsigned int _num, ...);								//重设委托，清空内存空间，并使其委托_num个函数，_num后必须有且只有_num个函数指针作为参数
	void __cdecl append(unsigned int _num, ...);							//在后面添加_num个委托，_num后必须有且只有_num个函数指针作为参数
	void allocate(unsigned int _num);										//重设委托，并重新分配_num个函数指针的空间，且至少为1
	void reallocate();														//将分配的内存空间缩小到与当前委托的函数的数量相同
	void change(FUNPTR _From, FUNPTR _To);									//将所有_from指向的函数替换为_to指向的函数
	void insert(unsigned int _Pos, FUNPTR _Func);							//在_Pos位置插入函数_Func，若_Pos >= _func_num则在尾部插入
	void insert(unsigned int _Pos, const FUNPTR* const _Start, int _Num);	//在_Pos位置插入从函数_Start开始的_Num个函数
	void erase(unsigned int _Pos, unsigned int _Num = 1);					//删除从_Pos开始的_Num个函数，_Num默认为1
	[[nodiscard]] unsigned int find(FUNPTR _toFind) const;								//寻找_toFind指向的函数出现的第一个位置，若找不到，返回Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int find(unsigned int _StartPos, FUNPTR _ToFind) const;		//寻找从_startPos位置开始的_toFind指向的函数出现的第一个位置，若找不到，返回Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int rfind(FUNPTR _ToFind) const;								//寻找_toFind指向的函数出现的最后一个位置，若找不到，返回Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int rfind(unsigned int _EndPos, FUNPTR _ToFind) const;		//寻找从_endPos之前的_toFind指向的函数出现的最后一个位置，若找不到，返回Timothy::delegate<_Rtn, _arg...>::npos

	
	//以下操作符均不会缩小已分配的内存空间

	_Rtn operator() (_arg...) const;										//逐个调用委托的各个函数，返回最后一个调用的函数的返回值
	delegate& operator= (const delegate& _newdelg);							//委托之间相互赋值
	delegate& operator= (delegate && _newdelg) noexcept;					//委托的移动赋值
	delegate& operator= (FUNPTR _newfunc);									//给委托重新赋值，成为单播委托
	delegate& operator+= (const delegate& _adddelg);						//在委托尾部添加另一个委托_adddelg
	delegate& operator+= (FUNPTR _addfunc);									//在尾部添加_addfunc指向的函数
	delegate& operator-= (const delegate& _subdelg);						//清除另一个委托_subdelg委托的所有函数在本委托中最后的委托
	delegate& operator-= (FUNPTR _subfunc);									//清除最后一个_addfunc指向的函数
	delegate& operator*= (unsigned int times);								//将委托翻倍，即重复times次
	[[nodiscard]] delegate operator+ (const delegate& _adddelg) const;		//返回一个委托，为两个委托相加
	[[nodiscard]] delegate operator+ (FUNPTR _addfunc) const;				//返回一个委托，为一个委托与一个函数相加
	[[nodiscard]] delegate operator- (const delegate& _subdelg) const;		//返回一个委托，为前一个委托清除后一个委托_subdelg委托的所有函数在前一个委托中最后的委托
	[[nodiscard]] delegate operator- (FUNPTR _subfunc) const;				//返回一个委托，为原委托清除最后一个_addfunc指向的函数后得到的委托
	[[nodiscard]] delegate operator* (unsigned int times) const;			//返回一个委托，为一个委托重复times次
	FUNPTR& operator[] (unsigned int _Pos);									//返回第_Pos个委托的函数的指针，如果_Pos超过了委托的函数个数，则抛出异常Timothy::out_range
	const FUNPTR& operator[] (unsigned int _Pos) const;						//返回第_Pos个委托的函数的指针，如果_Pos超过了委托的函数个数，则抛出异常Timothy::out_range
	[[nodiscard]] unsigned int NumOfFuncs() const { return _func_num; }		//返回当前委托的函数的个数
	[[nodiscard]] bool empty() const { return !_func_num; }					//判断委托是否为空

	//获取委托的各项属性

	[[nodiscard]] inline unsigned int number() const { return _func_num; }	//获取当前委托的函数个数
	[[nodiscard]] inline unsigned int capacity() const { return _capacity; }//获取当前委托的容量

	//析构函数

	~delegate() { delete[] _fp; }

protected:
	FUNPTR* _fp;
	unsigned int _func_num;
	unsigned int _capacity;
}; 

template <typename... _arg>
using Action = delegate<void, _arg...>;										//无返回值的委托

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(unsigned int _num, ...)
{
	if (!_num)
	{
		_fp = new FUNPTR[1];
		_capacity = 1;
		_func_num = 0;
		return;
	}
	_fp = new FUNPTR[_num];
	_capacity = _func_num = _num;
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(FUNPTR* _First, FUNPTR* _Last)
{
	if (_First == _Last)
	{
		_fp = new FUNPTR[1];
		_capacity = 1;
		_func_num = 0;
		return;
	}
	_fp = new FUNPTR[_capacity = _func_num = _Last - _First];
	for (unsigned int i = 0; i < _func_num; ++i)
		_fp[i] = _First[i];
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(const delegate& _srcdelg)
{
	if (&_srcdelg == this)
	{
		_capacity = 1;
		_func_num = 0;
		_fp = new FUNPTR[1];
		return;
	}
	_capacity = _func_num = _srcdelg._func_num;
	_fp = new FUNPTR[_func_num];
	for (int i = 0; i < _func_num; ++i)
		_fp[i] = _srcdelg[i];
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::reset(unsigned int _num, ...)
{
	if (_capacity < _num)
	{
		delete[] _fp;
		_fp = new FUNPTR[_capacity = _num];
	}
	_func_num = _num;
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::clear()
{
	delete[] _fp;
	_func_num = 0;
	_capacity = 1;
	_fp = new FUNPTR[1];
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::clear(FUNPTR _newfunc)
{
	delete[] _fp; 
	_fp = new FUNPTR[1]; 
	_fp[0] = _newfunc; 
	_func_num = _capacity = 1; 
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::clear(unsigned int _num, ...)
{
	delete[] _fp;
	_func_num = _num;
	if (!_num)
	{
		_fp = new FUNPTR[_capacity = 1];
		return;
	}
	_fp = new FUNPTR[_capacity = _num];
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::append(unsigned int _num, ...)
{
	if (!_num) return;
	if (_func_num + _num > _capacity)
	{
		while ((_capacity *= 2) < _func_num + _num);
		FUNPTR* newAlloc = new FUNPTR[_capacity];
		for (unsigned int i = 0; i < _func_num; ++i)
			newAlloc[i] = _fp[i];
		delete[] _fp;
		_fp = newAlloc;
	}
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = _func_num; i < _func_num + _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
	_func_num += _num;
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::allocate(unsigned int _num)
{
	delete[] _fp;
	if (!_num) ++_num;
	_capacity = _num;
	_func_num = 0;
	_fp = new FUNPTR[_num];
} 

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::reallocate()
{
	if (_capacity == _func_num || _capacity == 1) return; 
	FUNPTR* newfp; 
	if (_func_num)
	{
		newfp = new FUNPTR[_func_num]; 
		for (unsigned int i = 0; i < _func_num; ++i)
			newfp[i] = _fp[i]; 
	}
	else newfp = new FUNPTR[1]; 
	delete[] _fp; 
	_fp = newfp; 
}

template <typename _Rtn, typename..._arg>
_Rtn delegate<_Rtn, _arg...>::operator()(_arg... argu) const
{
	if (!_func_num) throw empty_delegate();
	for (unsigned int i = 0; i < _func_num - 1; ++i)
		_fp[i](argu...);
	return _fp[_func_num - 1](argu...);
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (const delegate& _newdelg)
{
	if (&_newdelg == this) return *this;
	_func_num = _newdelg._func_num;
	if (_capacity < _newdelg._func_num)
	{
		delete[] _fp;
		_fp = new FUNPTR[_capacity = _func_num];
	}
	for (unsigned int i = 0; i < _func_num; ++i)
		_fp[i] = _newdelg._fp[i];
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (delegate&& _newdelg) noexcept
{
	delete[] _fp;
	_func_num = _newdelg._func_num;
	_capacity = _newdelg._capacity;
	_newdelg._func_num = _newdelg._capacity = 0;
	_fp = _newdelg._fp;
	_newdelg._fp = nullptr;
	return *this;
}

template <typename _Rtn, typename..._arg>
inline delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (FUNPTR _newfunc)
{
	_func_num = 1;
	_fp[0] = _newfunc;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator+= (const delegate& _adddelg)
{
	if (_adddelg._func_num == 0) return *this;
	if (_capacity >= _func_num + _adddelg._func_num)
	{
		for (unsigned int i = 0; i < _adddelg._func_num; ++i)
			_fp[_func_num + i] = _adddelg._fp[i];
		_func_num += _adddelg._func_num;
		return *this;
	}
	while ((_capacity *= 2) < _func_num + _adddelg._func_num);
	FUNPTR* tmp = new FUNPTR[_capacity];
	for (unsigned int i = 0; i < _func_num; ++i)
		tmp[i] = _fp[i];
	for (unsigned int j = 0; j < _adddelg._func_num; ++j)
		tmp[_func_num + j] = _adddelg._fp[j];
	_func_num += _adddelg._func_num;
	delete[] _fp;
	_fp = tmp;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator+= (FUNPTR _addfunc)
{
	if (_capacity < _func_num + 1)
	{
		_capacity *= 2;
		FUNPTR* tmp = new FUNPTR[_capacity];
		for (unsigned int i = 0; i < _func_num; ++i)
			tmp[i] = _fp[i];
		delete[] _fp;
		_fp = tmp;
	}
	_fp[_func_num++] = _addfunc;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator-= (const delegate& _subdelg)
{
	if (_func_num == 0) return *this; 
	if (&_subdelg == this)
	{
		_func_num = 0; 
		return *this; 
	}
	std::set<unsigned int> delPos; 
	for (unsigned int i = 0; i < _subdelg._func_num; ++i)
		for (unsigned int j = _func_num - 1; ; --j)
		{
			if (_fp[j] == _subdelg._fp[i] && delPos.find(j) == delPos.end())
			{
				delPos.insert(j);
				break;
			}
			if (j == 0) break; 
		}
	unsigned int delNum = 0, i = 0, dest; 
	auto calDest = [&]() {return *delPos.begin() < delNum ? 0 : *delPos.begin() - delNum; }; 
	while (!delPos.empty())
	{
		dest = calDest(); 
		delPos.erase(delPos.begin()); 
		for (; i < dest; ++i)
		{
			if (delNum) _fp[i] = _fp[i + delNum]; 
		} 
		++delNum; 
	}
	if (delNum)
	{
		_func_num -= delNum; 
		dest = _func_num - delNum; 
		for (; i < _func_num; ++i) _fp[i] = _fp[i + delNum];
	} 
	return *this; 
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator-= (FUNPTR _subfunc)
{
	if (_func_num == 0) return *this; 
	for (unsigned int i = _func_num - 1; ; --i)
	{
		if (_fp[i] == _subfunc)
		{
			--_func_num; 
			for (; i < _func_num; ++i) _fp[i] = _fp[i + 1];
			break;
		}
		if (i == 0) break; 
	}
	return *this; 
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator*= (unsigned int times)
{
	if (_func_num == 0u) return *this; 
	if (_capacity < _func_num * times)
	{
		do { _capacity *= 2; } while (_capacity < _func_num * times);
		FUNPTR* tmp = new FUNPTR[_capacity]; 
		for (unsigned int i = 0; i < _func_num; ++i)
			tmp[i] = _fp[i]; 
		delete[] _fp; 
		_fp = tmp; 
	}
	unsigned int num = _func_num; 
	times -= 1; 
	for (unsigned int i = 0; i < times; ++i)
		for (unsigned int j = 0; j < num; ++j)
			_fp[_func_num++] = _fp[j]; 
	return *this; 
}



__TIMOTHY_NAMESPACE_END

#endif
