#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::vector<int>::iterator iter = 
		values.erase(std::remove_if(values.begin(), 
									values.end(), 
									[](const int &value) { return (value > 3); }), 
					 values.end());

	return 0;
}
