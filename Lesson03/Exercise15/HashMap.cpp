#include "HashMap.h"

HashMap::HashMap(int capacity)
	: m_values1(std::vector<int>(capacity, -1))
	, m_values2(std::vector<int>(capacity, -1))
	, m_capacity(capacity)
{}

int HashMap::hash1(int value) const
{
	return value % m_capacity;
}

int HashMap::hash2(int value) const
{
	return hash1(value) % m_capacity;
}

std::vector<int>::iterator HashMap::find(int value)
{
	int key = hash1(value);

	// value가 m_values1에 있는 경우
	if (m_values1[key] == value)
	{
		return m_values1.begin() + key;
	}

	key = hash2(value);

	// value가 m_values2에 있는 경우
	if (m_values2[key] == value)
	{
		return m_values2.begin() + key;
	}

	// value가 없는 경우
	return m_values2.end();
}


