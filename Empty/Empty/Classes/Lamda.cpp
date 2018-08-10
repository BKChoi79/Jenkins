#include "Lamda.h"
#include <vector>


Lamda::Lamda()
{
}

Lamda::~Lamda()
{
}

void Lamda::foo()
{
	vector<int> list;
	list.push_back(100);
	list.push_back(200);
	list.push_back(900);
	list.push_back(300);
	list.push_back(400);
	list.push_back(500);
	list.push_back(700);

	auto orderByDESC = [](int a, int b) -> bool
	{
		if (a > b)
			return true;
		else
			return false;
	};

	auto orderByASC = [](int a, int b) -> bool
	{
		if (a < b)
			return true;
		else
			return false;
	};

	sort(list.begin(), list.end(), orderByDESC);
	for (auto n : list)
	{
		printf("%d\n", n);
	}

	bool is_even = [](int n){ return n % 2 == 0; }(41);

	int a = 10, b = 20, c = 30;
	int nSum = [a, b]
	{
		return a + b;
	} ();

}