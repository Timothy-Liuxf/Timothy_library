
#include "PriorityQueue_Tim.h"
#include "Queue_Tim.h"
#include "Stack_Tim.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <string>

using Timothy::PriorityQueue;
using Timothy::Queue;
using Timothy::Stack;
using std::cout;
using std::endl;
using std::vector;

template <typename T>
void Foo(T && r)
{
	r = 4;
	cout << typeid(r).name() << endl;
}


int main()
{
	try
	{
		Stack<double> s;
		for (int i = 0; i < 10; ++i)
		{
			s.Push(i);
		}

		cout << s.Size() << endl;

		for (int i = 0; i < 5; ++i)
		{
			cout << s.PopTop() << endl;
		}

		auto s1 = s;

		while (!s.Empty())
		{
			cout << s.Top() << endl;
			s.Pop();
		}

		while (!s1.Empty())
		{
			cout << s1.Top() << endl;
			s1.Pop();
		}
	}
	catch (Timothy::t_exception e)
	{
		cout << e << endl;
	}
	return 0;
}
