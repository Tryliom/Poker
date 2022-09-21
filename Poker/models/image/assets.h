#pragma once
#include "CardImage.h"

#include <vector>

class Assets
{
private:
	std::vector<std::vector<CardImage>> _cards;
	CardImage _hiddenCard;

public:
	Assets();

	CardImage GetHiddenCard() const { return _hiddenCard; }
	CardImage GetCard(const Card card) const { return _cards[static_cast<int>(card.GetSuit())][static_cast<int>(card.GetValue())]; }
};

