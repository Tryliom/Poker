#pragma once
#include <vector>

#include "card.h"

class Deck
{
	private:
		std::vector<Card> _cards;

	public:
		Deck();
		Card PickRandomCard();
		std::string ToString() const;

};

