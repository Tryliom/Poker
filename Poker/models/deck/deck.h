#pragma once
#include <vector>

#include "card.h"

class Deck
{
	private:
		std::vector<Card> _cards;

	public:
		Deck();
		/**
		 * @brief Pick a random card from deck and delete it from the deck
		 * @return {Card} A unique card from the deck
		 */
		Card PickRandomCard();
		std::string ToString() const;

};

