#include "CardDeck.h"

int main()
{
	CardDeck deck = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

	for (int cntChoice = 1; cntChoice <= 5; ++cntChoice)
	{
		const int idxCard = deck.getIdxCardRandomly();
		std::cout << cntChoice << "th choice: " << deck[idxCard] << "\n";

		deck.pop(idxCard);

		deck.shuffle();
		std::cout << deck << "\n";
	}

	return 0;
}
