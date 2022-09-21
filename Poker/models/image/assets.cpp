#include "Assets.h"
#include "../deck/card.h"

Assets::Assets()
{
	_cards = {};
	// Loop in suits and values to insert every type of cards inside the assets
	for (int suit = static_cast<int>(CardSuit::CLUBS); suit < static_cast<int>(CardSuit::END); suit++)
	{
		std::vector<CardImage> suitImages = {};
		for (int value = static_cast<int>(CardValue::TWO); value < static_cast<int>(CardValue::END); value++)
		{
			Card card(static_cast<CardSuit>(suit), static_cast<CardValue>(value));

			if (card.GetValue() == CardValue::ACE)
			{
				suitImages.emplace_back(CardImage("assets/images/cards/ace_" + std::to_string(suit) + ".txt", card.GetSuit()));
			}
			else
			{
				suitImages.emplace_back(CardImage("assets/images/cards/card_" + std::to_string(value) + ".txt", card.GetSuit()));
			}
		}

		_cards.emplace_back(suitImages);
	}

	_hiddenCard = CardImage("assets/images/cards/hidden_card.txt");
}
