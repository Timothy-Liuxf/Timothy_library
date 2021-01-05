#ifndef PRIORITY_QUEUE_TIM_H

#define PRIORITY_QUEUE_TIM_H

#include <exception_Tim.h>
#include <Algorithm_Tim.h>
#include <initializer_list>
#include <utility>
#include <cstring>

__TIMOTHY_NAMESPACE_BEGIN

template <typename ElemType, typename Pred = Less<ElemType>>
class PriorityQueue
{
public:
	using SizeType = unsigned int;

	PriorityQueue() : capacity(0), size(0), heap(nullptr) {}
	
	template <typename Ptr>
	PriorityQueue(Ptr first, Ptr last)
	{
		size = (SizeType)(last - first);
		if (size == 0)
		{
			heap = nullptr;
			return;
		}

		heap = new ElemType[capacity = size];

		SizeType fullTree = 2;
		while (fullTree - 1 < size) fullTree <<= 1;
		fullTree >>= 1;

		SizeType tmpHeapPos = size;
		Ptr tmp = first;

		while (tmp != last)
		{
			heap[--tmpHeapPos] = *tmp;
			++tmp;
			HeapifyFromTopToBottom(tmpHeapPos);
		}
	}

	PriorityQueue(std::initializer_list<ElemType> lst) : PriorityQueue(lst.begin(), lst.end()) {}

	PriorityQueue& operator=(const PriorityQueue& srcPQ)
	{
		if (&srcPQ != this) Copy(srcPQ);
		return *this;
	}

	PriorityQueue& operator=(PriorityQueue&& srcPQ) noexcept
	{
		if (&srcPQ != this) Copy(::std::move(srcPQ));
		return *this;
	}

	PriorityQueue(const PriorityQueue& srcPQ)
	{
		heap = nullptr;
		if (&srcPQ == this)
		{
			capacity = size = 0;
			return;
		}
		Copy(srcPQ);
	}

	PriorityQueue(PriorityQueue&& srcPQ) noexcept
	{
		heap = nullptr;
		if (&srcPQ == this)
		{
			capacity = size = 0;
			return;
		}
		Copy(::std::move(srcPQ));
	}

	bool Empty() const { return size == 0; }

	void Reserve(SizeType newCapacity)
	{
		if (newCapacity < size || newCapacity == capacity) return;
		if ((capacity = newCapacity) == 0)
		{
			delete[] heap;
			heap = nullptr;
		}
		else if (size == 0)
		{
			delete[] heap;
			heap = new ElemType[newCapacity];
		}
		else
		{
			ElemType* newHeap = new ElemType[capacity];
			for (SizeType i = 0; i < size; ++i)
			{
				newHeap[i] = heap[i];
			}
			delete[] heap;
			heap = newHeap;
		}
	}

	SizeType Capacity() const { return capacity; }
	SizeType MaxSize() const { return capacity; }
	SizeType Size() const { return size; }

	const ElemType& Front() const
	{
		if (Empty()) throw empty_collection("PriorityQueue");
		return heap[0];
	}

	void Pop()
	{
		if (Empty()) throw empty_collection("PriorityQueue");
		PopHeap();
	}

	ElemType PopFront()
	{
		if (Empty()) throw empty_collection("PriorityQueue");
		ElemType ret = heap[0];
		PopHeap();
		return ret;
	}

	void Push(const ElemType& newElem)
	{
		if (capacity == 0)
		{
			heap = new ElemType[1];
			capacity = 1;
		}
		else if (size == capacity)
		{
			capacity <<= 1;
			ElemType* newHeap = new ElemType[capacity];
			for (SizeType i = 0; i < size; ++i)
			{
				newHeap[i] = heap[i];
			}
			delete[] heap;
			heap = newHeap;
		}
		heap[size++] = newElem;
		SizeType newElemPos = size - 1, parentPos;
		while (newElemPos > 0)
		{
			parentPos = ((newElemPos - 1) >> 1);
			if (cmpFunc(heap[parentPos], newElem))
			{
				heap[newElemPos] = heap[parentPos];
				heap[parentPos] = newElem;
				newElemPos = parentPos;
			}
			else break;
		}
	}

	void Clear() { size = 0; }

	~PriorityQueue() { delete heap; heap = nullptr; capacity = size = 0; }

private:

	SizeType capacity;
	SizeType size;
	ElemType* heap;
	Pred cmpFunc;

	void PopHeap()
	{
		heap[0] = heap[--size];
		HeapifyFromTopToBottom(0);
	}

	void HeapifyFromTopToBottom(SizeType repairElemPos)
	{
		SizeType leftChildPos = (repairElemPos << 1) + 1, rightChildPos = leftChildPos + 1, biggerChildPos;
		while (leftChildPos < size)
		{
			if (rightChildPos < size && cmpFunc(heap[leftChildPos], heap[rightChildPos])) biggerChildPos = rightChildPos;
			else biggerChildPos = leftChildPos;
			if (cmpFunc(heap[repairElemPos], heap[biggerChildPos]))
			{
				Swap(heap[biggerChildPos], heap[repairElemPos]);
				repairElemPos = biggerChildPos;
				leftChildPos = (repairElemPos << 1) + 1;
				rightChildPos = leftChildPos + 1;
			}
			else break;
		}
	}


	void Copy(const PriorityQueue& srcPQ)
	{
		delete[] heap;
		size = capacity = srcPQ.size;
		if (capacity == 0) heap = nullptr;
		else
		{
			heap = new ElemType[capacity];
			for (SizeType i = 0; i < size; ++i)
			{
				heap[i] = srcPQ.heap[i];
			}
		}
	}

	void Copy(PriorityQueue&& srcPQ) noexcept
	{
		delete[] heap;
		size = srcPQ.size;
		capacity = srcPQ.capacity;
		heap = srcPQ.heap;
		srcPQ.heap = nullptr;
		srcPQ.size = 0;
		srcPQ.capacity = 0;
	}

};

__TIMOTHY_NAMESPACE_END

#endif	//ifndef PRIORITY_QUEUE_H
