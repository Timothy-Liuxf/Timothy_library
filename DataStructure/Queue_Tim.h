#ifndef QUEUE_TIM_H
#define QUEUE_TIM_H

#include <exception_Tim.h>
#include <cstring>

__TIMOTHY_NAMESPACE_BEGIN

template <typename ElemType>
class Queue
{
public:
	using SizeType = unsigned int;

	Queue() : q(nullptr), capacity(0), size(0), head(0), tail(0) {}

	Queue(SizeType maxSize) : capacity(maxSize + 1), size(0), head(0), tail(0), q(maxSize > 0 ? new ElemType[capacity] : nullptr) {}

	Queue& operator=(const Queue& srcQ)
	{
		if (&srcQ != this) Copy(srcQ);
		return *this;
	}

	Queue& operator=(Queue&& srcQ) noexcept
	{
		if (&srcQ != this) Copy(::std::move(srcQ));
		return *this;
	}

	Queue(const Queue& srcQ)
	{
		q = nullptr;
		if (&srcQ == this)
		{
			capacity = size = head = tail = 0;
			return;
		}
		Copy(srcQ);
	}

	Queue(Queue&& srcQ) noexcept
	{
		q = nullptr;
		if (&srcQ == this)
		{
			capacity = size = head = tail = 0;
			return;
		}
		Copy(::std::move(srcQ));
	}

	bool Empty() const { return head == tail; }

	void Push(const ElemType& newElem)
	{
		if (capacity == 0)
		{
			q = new ElemType[2];
			capacity = 2;
		}
		else if ((tail + 1) % capacity == head)
		{
			ElemType* newQ = new ElemType[capacity << 1];
			SizeType newTail = 0;
			if (head > tail)
			{
				while (head < capacity) newQ[newTail++] = q[head++];
				head = 0;
				while (head < tail) newQ[newTail++] = q[head++];
				delete[] q;
				q = newQ;
				head = 0;
				tail = newTail;
			}
			else
			{
				while (head < tail) newQ[newTail++] = q[head++];
				delete[] q;
				q = newQ;
				head = 0;
				tail = newTail;
			}
			capacity <<= 1;
		}
		++size;
		q[tail] = newElem;
		if (++tail == capacity) tail = 0;
	}

	void Pop()
	{
		if (Empty()) throw empty_collection("Queue");
		if (++head == capacity) head = 0;
		--size;
	}

	const ElemType& PopFront()
	{
		if (Empty()) throw empty_collection("Queue");
		ElemType* ret = q + head;
		if (++head == capacity) head = 0;
		--size;
		return *ret;
	}

	const ElemType& Front() const { if (Empty()) throw empty_collection("Queue"); return q[head]; }
	
	SizeType Size() const { return size; }

	SizeType MaxSize() const { return capacity ? capacity - 1 : 0; }
	SizeType Capacity() const { return capacity; }

	void Clear()
	{
		head = tail = size = 0;
	}

	~Queue()
	{
		delete[] q;
		q = nullptr;
		head = tail = size = capacity = 0;
	}

private:

	ElemType* q;
	SizeType head;
	SizeType tail;
	SizeType size;
	SizeType capacity;


	void Copy(const Queue& srcQ)
	{
		delete[] q;
		::std::memcpy(this, &srcQ, sizeof(*this));
		q = (srcQ.capacity > 0 ? new ElemType[srcQ.capacity] : nullptr);
		for (SizeType i = 0; i < size; ++i)
		{
			q[i] = srcQ.q[i];
		}
	}

	void Copy(Queue&& srcQ) noexcept
	{
		delete[] q;
		std::memcpy(this, &srcQ, sizeof(*this));
		std::memset(&srcQ, 0, sizeof(srcQ));
	}

};

__TIMOTHY_NAMESPACE_END

#endif //!QUEUE_TIM_H
