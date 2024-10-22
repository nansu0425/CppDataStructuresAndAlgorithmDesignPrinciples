#include "CircularLinkedList.h"

int main()
{
	CircularLinkedList<int> list = {0, 1, 2, 3, 4};

	list.insert(list.begin(), -1);
	list.insert(list.find(3), 2);
	list.remove(list.find(1));
	list.remove(list.find(0));

	std::cout << list << '\n';

	return 0;
}