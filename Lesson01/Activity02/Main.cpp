#include "Player.h"

int main()
{
	PlayerManager playerManager(4);

	while (playerManager.getNumPlayersCardsEmpty() == 0)
	{
		playerManager.chooseCardPlayers();
		playerManager.printPlayers();
		
		if (playerManager.isMatchingCards())
		{
			playerManager.removeMatchingCards();
		}

		std::cout << "----------------------------------------------\n";
	}

	if (playerManager.getNumPlayersCardsEmpty() == 1)
	{
		std::cout << "Winner\n";
	}
	else
	{
		std::cout << "Draw\n";
	}

	playerManager.printPlayersCardsEmpty();

	return 0;
}
