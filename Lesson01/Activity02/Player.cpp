#include "Player.h"

#include <cassert>

Player::Player()
{
	static int s_nexId = 0;

	m_id = s_nexId;
	++s_nexId;
}

int Player::chooseCard()
{
	m_curIdxCard = m_deck.getIdxCardRandomly();

	return m_deck[m_curIdxCard];
}

void Player::removeCard()
{
	assert(m_curIdxCard != -1);

	m_deck.remove(m_curIdxCard);
	m_curIdxCard = -1;
}

PlayerManager::PlayerManager(int numPlayers)
	: m_players(numPlayers)
{}

void PlayerManager::chooseCardPlayers()
{
	assert(getNumPlayersCardsEmpty() == 0);
	
	m_cardsChosen.clear();
	m_cardToPlayer.clear();

	for (Player& player : m_players)
	{
		m_cardToPlayer.insert(std::pair<int, Player&>(player.chooseCard(), player));
		m_cardsChosen.insert(player.getCardChosen());
	}
}

void PlayerManager::removeMatchingCards()
{
	for (int card : m_cardsChosen)
	{
		while (m_cardToPlayer.count(card) >= 2)
		{
			auto end = m_cardToPlayer.find(card);
			auto cur = end;
			std::advance(end, 2);

			while (cur != end)
			{
				cur->second.removeCard();
				if (cur->second.isCardDeckEmpty())
				{
					m_playerIdsCardsEmpty.insert(cur->second.getId());
				}

				auto erased = cur;
				++cur;
				m_cardToPlayer.erase(erased);
			}
		}
	}
}

void PlayerManager::printPlayers() const
{
	for (int id = 0; id < m_players.size(); ++id)
	{
		std::cout << "[Player " << id << "]\n";
		std::cout << "Card deck: " << m_players[id].getCardDeck() << "\n";
		std::cout << "Card chosen: " << m_players[id].getCardChosen() << "\n";
	}
}

void PlayerManager::printPlayersCardsEmpty() const
{
	for (int id : m_playerIdsCardsEmpty)
	{
		std::cout << "[Player " << id << "]\n";
	}
}
