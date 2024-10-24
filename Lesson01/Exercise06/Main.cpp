#include <iostream>
#include <list>
#include <algorithm>

int main()
{
	std::list<int> list1 = {1, 2, 3, 4, 5};
	list1.emplace_back(6);

	auto iter = list1.begin();
	list1.insert(iter, 0);

	iter = list1.end();
	list1.insert(iter, 7);

	list1.pop_back();

	// std::advance(iter, 1); end iterator를 넘어갈 수 없다
	std::advance(iter, -3);

	return 0;
}