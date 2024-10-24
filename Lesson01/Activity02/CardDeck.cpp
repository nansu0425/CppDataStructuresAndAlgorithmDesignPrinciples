#include "CardDeck.h"

#include <cassert>

std::ostream& operator<<(std::ostream& os, const CardDeck& deck)
{
	auto iter = deck.m_stack.begin();
	
	os << *iter;
	++iter;

	while (iter != deck.m_stack.begin() + deck.m_idxTop + 1)
	{
		os << ", " << *iter;
		++iter;
	}

	return os;
}

void CardDeck::shuffle()
{
	std::shuffle(m_stack.begin(), m_stack.begin() + m_idxTop + 1, m_rng);
}

void CardDeck::pop()
{
	assert(m_idxTop >= 0);

	const int card = m_stack[m_idxTop];
	--m_idxTop;
}

void CardDeck::pop(int idx)
{
	std::swap(m_stack[idx], m_stack[m_idxTop]);
	pop();
}

int CardDeck::getIdxCardRandomly()
{
	std::uniform_int_distribution<> distIdx(0, m_idxTop);
	
	return distIdx(m_rng);
}
