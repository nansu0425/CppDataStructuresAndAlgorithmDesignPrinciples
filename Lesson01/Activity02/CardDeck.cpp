#include "CardDeck.h"

#include <cassert>

CardDeck::CardDeck()
	: m_stack(s_numCards)
{
	std::random_device rd;
	std::seed_seq seed = {rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
	m_rng = std::mt19937(seed);

	for (int card = 0; card < s_numCards; ++card)
	{
		m_stack[card] = card;
	}

	shuffle();
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

void CardDeck::remove(int idx)
{
	std::swap(m_stack[idx], m_stack[m_idxTop]);
	pop();
}

int CardDeck::getIdxCardRandomly()
{
	std::uniform_int_distribution<> distIdx(0, m_idxTop);
	
	return distIdx(m_rng);
}

std::ostream& operator<<(std::ostream& os, const CardDeck& deck)
{
	if (deck.isEmpty())
	{
		os << "Empty";
		return os;
	}

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
