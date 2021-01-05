#ifndef STACK_TIM_H

#define STACK_TIM_H

#include <exception_Tim.h>

__TIMOTHY_NAMESPACE_BEGIN

template <typename ElemType>
class Stack
{
public:
	using SizeType = unsigned int;

	Stack() : stack(nullptr), capacity(0), size(0) {}

	Stack(SizeType maxSize) : capacity(maxSize), stack(maxSize ? new ElemType[maxSize] : nullptr), size(0) {}

	Stack(const Stack& srcStk)
	{
		stack = nullptr;
		if (&srcStk != this) Copy(srcStk);
	}

	Stack(Stack&& srcStk) noexcept
	{
		stack = nullptr;
		if (&srcStk != this) Copy(::std::move(srcStk));
	}

	~Stack() { delete[] stack; stack = nullptr; capacity = 0; size = 0; }

	Stack& operator=(const Stack& srcStk)
	{
		if (&srcStk != this) Copy(srcStk);
		return *this;
	}

	Stack& operator=(Stack&& srcStk)
	{
		if (&srcStk != this) Copy(::std::move(srcStk));
		return *this;
	}

	SizeType Size() const { return size; }
	SizeType Capacity() const { return capacity; }
	SizeType MaxSize() const { return capacity; }
	bool Empty() const { return size == 0; }

	void Push(const ElemType &newElem)
	{
		if (capacity == 0)
		{
			capacity = 1;
			stack = new ElemType[1];
		}
		else if (size == capacity)
		{
			ElemType *newStack = new ElemType[capacity <<= 1];
			for (SizeType i = 0; i < size; ++i)
			{
				newStack[i] = stack[i];
			}
			delete[] stack;
			stack = newStack;
		}
		stack[size++] = newElem;
	}

	void Pop()
	{
		if (Empty()) throw empty_collection("Stack");
		--size;
	}

	ElemType Top() const
	{
		if (Empty()) throw empty_collection("Stack");
		return stack[size - 1];
	}

	ElemType PopTop()
	{
		if (Empty()) throw empty_collection("Stack");
		return stack[--size];
	}

private:

	ElemType *stack;
	SizeType capacity;
	SizeType size;

	void Copy(const Stack &srcStk)
	{
		delete[] stack;
		capacity = size = srcStk.size;
		if (capacity)
		{
			stack = new ElemType[capacity];
			for (SizeType i = 0; i < size; ++i) stack[i] = srcStk.stack[i];
		}
		else stack = nullptr;
	}

	void Copy(Stack &&srcStk)
	{
		delete[] stack;
		::std::memcpy(this, &srcStk, sizeof(srcStk));
		srcStk.stack = nullptr;
		srcStk.capacity = srcStk.size = 0;
	}

};

__TIMOTHY_NAMESPACE_END

#endif
