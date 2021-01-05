#ifndef ALGORITHM_TIM_H

#define ALGORITHM_TIM_H

#include <Timothy_all.h>

__TIMOTHY_NAMESPACE_BEGIN

template <typename ElemType>
inline void Swap(ElemType& elem1, ElemType& elem2)
{
	ElemType tmp = elem1;
	elem1 = elem2;
	elem2 = tmp;
}


template <typename Elemtype>
struct Less
{
	bool operator()(const Elemtype& op1, const Elemtype& op2)
	{
		return op1 < op2;
	}
};

template <typename Elemtype>
struct Greater
{
	bool operator()(const Elemtype& op1, const Elemtype& op2)
	{
		return op1 > op2;
	}
};

template <typename StrPtr, typename SizeType = ::std::size_t>
SizeType KMP(StrPtr srcFirst, StrPtr srcLast, StrPtr subFirst, StrPtr subLast, SizeType FailVal = -1)
{
	//init next
	SizeType* next = new SizeType[subLast - subFirst];
	next[0] = 0;
	StrPtr iPtr = subFirst + 1, jPtr = subFirst;
	SizeType i = 1, j = 0;
	while (iPtr != subLast)
	{
		if (*iPtr == *jPtr)
		{
			next[i] = j + 1;
			++i, ++j, ++iPtr, ++jPtr;
		}
		else if (j)
		{
			j = next[j - 1];
			jPtr = subFirst + j;
		}
		else
		{
			next[i++] = 0; ++iPtr;
		}
	}

	iPtr = srcFirst, i = 0;
	jPtr = subFirst, j = 0;
	while (iPtr != srcLast)
	{
		if (*iPtr == *jPtr)
		{
			++jPtr;
			if (jPtr == subLast)
			{
				delete[] next;
				return i - j;
			}
			++iPtr; ++i; ++j;
		}
		else if (j)
		{
			j = next[j - 1];
			jPtr = subFirst + j;
		}
		else
		{
			++i; ++iPtr;
		}
	}
	delete[] next;
	return FailVal;
}

__TIMOTHY_NAMESPACE_END

#endif // ifndef ALGORITHM_TIM_H
