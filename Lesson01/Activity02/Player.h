#pragma once

#include "CardDeck.h"

#include <random>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

class Player
{
public:
	Player();

	int					chooseCard();
	void				removeCard();

	bool				isCardDeckEmpty() const	{ return m_deck.isEmpty(); }
	int					getCardChosen() const { return m_deck[m_curIdxCard]; }
	const CardDeck&		getCardDeck() const { return m_deck; }
	int					getId() const { return m_id; }
	bool				isCardChosen() const { return (m_curIdxCard != -1); }

private:
	CardDeck			m_deck;
	int					m_id;
	int					m_curIdxCard = -1;
};

class PlayerManager
{
private:
	using Vector		= std::vector<Player>;
	using MulMap		= std::unordered_multimap<int, Player&>;
	using Set			= std::unordered_set<int>;

public:
	PlayerManager(int numPlayers);

	void				chooseCardPlayers();
	void				removeMatchingCards();
	size_t				getNumPlayersCardsEmpty() const { return m_playerIdsCardsEmpty.size(); }
	bool				isMatchingCards() const { return (m_cardsChosen.size() < m_players.size()); }
	
	void				printPlayers() const;
	void				printPlayersCardsEmpty() const;

private:
	Vector				m_players;
	MulMap				m_cardToPlayer;
	Set					m_cardsChosen;
	Set					m_playerIdsCardsEmpty;
};
