#pragma once

#include <iostream>
#include <vector>

class HashMap
{
public:
	HashMap(int capacity);

	int hash1(int value) const;
	int hash2(int value) const;

	std::vector<int>::iterator find(int value);


private:
	std::vector<int>	m_values1;
	std::vector<int>	m_values2;
	int					m_capacity;
};
