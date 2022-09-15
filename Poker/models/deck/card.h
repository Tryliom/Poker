#pragma once
#include <string>

enum class Hand {
	CLUBS, HEARTS, SPADES, SQUARES, ENUM_END
};

enum class Value
{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, ENUM_END
};

class Card
{
	private:
		Hand _hand;
		Value _value;

		std::string handToString() const;
		std::string valueToString() const;
	public:
		Card(Hand hand, Value value);
		std::string ToString() const;
};

