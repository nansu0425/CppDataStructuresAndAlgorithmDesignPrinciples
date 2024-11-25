#include "HashMap.h"

#include <iostream>

int main()
{
	HashMap hm = HashMap(7);

	auto printLookUpResult = [&](const uint32_t value)
		{
			if (hm.find(value))
			{
				std::cout << "found " << value << std::endl;
			}
			else
			{
				std::cout << "couldn't find " << value << std::endl;
			}
		};

	hm.insert(2);
	hm.insert(25);
	hm.insert(10);
	printLookUpResult(25);

	hm.insert(100);
	printLookUpResult(100);
	printLookUpResult(2);

	return 0;
}
