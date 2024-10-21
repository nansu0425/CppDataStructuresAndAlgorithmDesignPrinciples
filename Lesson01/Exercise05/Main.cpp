#include "SinglyLinkedList.h"

#include <iostream>

int main()
{
	SinglyLinkedList li1 = {1, 2, 3};
	li1.pushFront(0);

	for (int i : li1)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';

	SinglyLinkedList li2 = li1;
	li2.pushFront(-1);

	for (int i : li2)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';

	return 0;
}