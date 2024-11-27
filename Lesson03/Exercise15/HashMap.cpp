#include "HashMap.h"

#include <iostream>

HashMap::HashMap(int capacity)
	: m_table(std::vector<int>(2 * capacity, -1))
	, m_capacity(capacity)
{}

int HashMap::hashLeft(int value) const
{
	return value % m_capacity;
}

int HashMap::hashRight(int value) const
{
	return m_capacity + ((value / m_capacity) % m_capacity);
}

std::vector<int>::iterator HashMap::find(int value)
{
	int key = hashLeft(value);

	// value가 left table에 있는 경우
	if (m_table[key] == value)
	{
		std::cout << "Found " << value << " in left table" << std::endl;

		return m_table.begin() + key;
	}

	key = hashRight(value);

	// value가 right table에 있는 경우
	if (m_table[key] == value)
	{
		std::cout << "Found " << value << " in right table" << std::endl;

		return m_table.begin() + key;
	}

	// value가 없는 경우
	std::cout << "Failed to find " << value << std::endl;

	return m_table.end();
}

void HashMap::remove(int value)
{
	std::vector<int>::iterator iterRemove = find(value);

	// 삭제할 값을 찾지 못 했다
	if (iterRemove == m_table.end())
	{
		std::cout << "Failed to remove " << value << std::endl;

		return;
	}

	*iterRemove = -1;
	std::cout << "Removed " << value << std::endl;
}

void HashMap::insert(int value)
{
	insertRecursively(value, 0, true);
	std::cout << std::endl;
}

void HashMap::insertRecursively(int value, int cntCall, bool isLeft)
{
	// 순환으로 간주
	if (cntCall >= m_capacity)
	{
		std::cout << "Failed to insert " << value << std::endl;

		return;
	}

	const int key = (isLeft) ? hashLeft(value) : hashRight(value);
	const int prevValue = m_table[key];

	m_table[key] = value;
	std::cout << "Inserted " << value;

	if (isLeft)
	{
		std::cout << " into left table";
	}
	else
	{
		std::cout << " into right table";
	}

	// 삽입 위치에 저장된 값이 있었다면 그 값은 다른 위치에 삽입
	if (prevValue != -1)
	{
		std::cout << " -> ";
		insertRecursively(prevValue, cntCall + 1, !isLeft);
	}
}
