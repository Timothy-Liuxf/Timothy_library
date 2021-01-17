#include "Extension_Tim.h"
#include <iostream>
#include <vector>

/*À©Õ¹¿â*/
using namespace std;

int main()
{
	vector<int> v { 2, 5, 6 };

	for (auto itr : Timothy::MakeReverse(v))
	{
		cout << itr << endl;
	}
	return 0;
}
