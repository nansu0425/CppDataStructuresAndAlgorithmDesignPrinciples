#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>

template<typename T>
class DynamicArray
{
public:
	DynamicArray(size_t size)
		: m_pData(new T[size])
		, m_size(size)
	{

	}

	DynamicArray(const DynamicArray& other)
		: m_pData(new T[other.m_size])
		, m_size(other.m_size)
	{
		std::copy(other.m_pData, other.m_pData + m_size, m_pData);
	}

	~DynamicArray()
	{
		if (m_pData != nullptr)
		{
			delete[] m_pData;
		}
	}

	size_t getSize() const
	{
		return m_size;
	}

	T& operator[](int index)
	{
		return m_pData[index];
	}

	const T& operator[](int index) const
	{
		return m_pData[index];
	}

	T& access(int index)
	{
		if (index < m_size)
		{
			return m_pData[index];
		}

		throw "Index out of range";
	}

	T* accessFisrt()
	{
		return m_pData;
	}

	const T* accessFisrt() const
	{
		return m_pData;
	}

	T* accessLast()
	{
		return m_pData + m_size;
	}

	const T* accessLast() const
	{
		return m_pData + m_size;
	}

	DynamicArray operator+(const DynamicArray& other) const
	{
		DynamicArray result(m_size + other.m_size);

		std::copy(m_pData, m_pData + m_size, result.m_pData);
		std::copy(other.m_pData, other.m_pData + other.m_size, result.m_pData + m_size);

		return result;
	}

	std::string convertToString(const std::string& sep = ", ") const
	{
		if (m_size == 0)
		{
			return "";
		}

		std::ostringstream oss;
		oss << m_pData[0];

		for (int idx = 1; idx < m_size; ++idx)
		{
			oss << sep << m_pData[idx];
		}

		return oss.str();
	}

private:
	T*			m_pData = nullptr;
	size_t		m_size = 0;
};
