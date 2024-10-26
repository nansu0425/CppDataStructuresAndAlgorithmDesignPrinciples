#pragma once

#include <vector>
#include <initializer_list>
#include <random>
#include <utility>
#include <iostream>
#include <algorithm>

class CardDeck
{
public:
	CardDeck();

	void					shuffle();
	void					pop();
	void					remove(int idx);
	int						getIdxCardRandomly();

	const int&				operator[](int idx) const { return m_stack[idx]; }
	friend std::ostream&	operator<<(std::ostream& os, const CardDeck& deck);

	bool					isEmpty() const { return (m_idxTop == -1); }

public:
	static constexpr size_t			s_numCards = 13;

private:
	std::vector<int>		m_stack;
	std::mt19937			m_rng;
	int						m_idxTop = s_numCards - 1;
};
