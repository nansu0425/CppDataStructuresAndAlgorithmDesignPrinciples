#include "HashMap.h"

HashMap::HashMap(Int4 capacity)
	: m_values(std::vector<Int4>(capacity, -1))
{}

HashMap::Uint4 HashMap::hash(Uint4 value)
{
	return (value % m_values.size());
}

void HashMap::insert(Uint4 value)
{
	m_values[hash(value)] = value;
}

bool HashMap::find(Uint4 value)
{
	return (m_values[hash(value)] == value);
}

void HashMap::erase(Uint4 value)
{
	if (!find(value))
	{
		return;
	}

	m_values[hash(value)] = -1;
}
