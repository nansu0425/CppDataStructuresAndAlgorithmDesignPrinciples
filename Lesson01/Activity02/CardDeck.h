#pragma once

#include <array>
#include <initializer_list>
#include <random>
#include <utility>
#include <iostream>
#include <algorithm>

class CardDeck
{
public:
	template<typename... Args>
	CardDeck(Args&&... args)
		: m_stack{std::forward<Args>(args)...}
		, m_rng(m_rd())
	{
		shuffle();
	}

	void	shuffle();
	void	pop();
	void	pop(int idx);
	int		getIdxCardRandomly();

	const int&				operator[](int idx) const { return m_stack[idx]; }
	friend std::ostream&	operator<<(std::ostream& os, const CardDeck& deck);

public:
	static constexpr size_t			s_numCards = 13;

private:
	std::array<int, s_numCards>		m_stack;
	int								m_idxTop = s_numCards - 1;
	std::random_device				m_rd;
	std::mt19937					m_rng;
};
