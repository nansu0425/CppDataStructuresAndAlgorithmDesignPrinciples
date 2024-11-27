#pragma once

#include <vector>

class HashMap
{
public:
	HashMap(int capacity);

	int hashLeft(int value) const;
	int hashRight(int value) const;

	std::vector<int>::iterator find(int value);
	void remove(int value);
	void insert(int value);

private:
	void insertRecursively(int value, int cntCall, bool isLeft);

private:
	std::vector<int>	m_table;
	int					m_capacity;
};
