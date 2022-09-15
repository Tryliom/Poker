#pragma once
#include "card.h"

enum class HandType
{
	HIGHCARD,
	PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH
};

class HandValue
{
private:
	HandType _handType;
	CardValue _higherSuit;
public:
	HandValue(HandType handType, CardValue higherSuit);

	bool IsBetter(HandValue other) const;
};