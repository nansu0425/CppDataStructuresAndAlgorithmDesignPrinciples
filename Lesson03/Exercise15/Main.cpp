#include "HashMap.h"

#include <iostream>

int main()
{
	HashMap hm = HashMap(7);

	hm.insert(10);
	hm.insert(20);
	hm.insert(30);
	std::cout << std::endl;

	hm.insert(104);
	hm.insert(2);
	hm.insert(70);
	hm.insert(9);
	hm.insert(90);
	hm.insert(2);
	hm.insert(7);
	std::cout << std::endl;

	hm.insert(14); // 사이클 발생!
	std::cout << std::endl;

	hm.remove(10);
	hm.remove(30);
	hm.remove(20);
	std::cout << std::endl;

	hm.remove(90);
	hm.remove(9);
	hm.remove(7);
	hm.remove(2);
	std::cout << std::endl;

	return 0;
}
