#pragma once

#include <vector>

class HashMap
{
private:
	using Uint4 = uint32_t;
	using Int4 = int32_t;

public:
	HashMap(Int4 capacity);

	Uint4 hash(Uint4 value);
	void insert(Uint4 value);
	bool find(Uint4 value);
	void erase(Uint4 value);

private:
	std::vector<Int4> m_values;
};
