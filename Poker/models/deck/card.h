#pragma once
#include <string>

enum class Suit {
	CLUBS, HEARTS, SPADES, DIAMONDS, END
};

enum class Value
{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, END
};

class Card
{
	private:
		Suit _hand;
		Value _value;

		std::string handToString() const;
		std::string valueToString() const;
	public:
		Card(Suit hand, Value value);

		/**
		 * \brief Return the card as a string
		 */
		explicit operator std::string() const
		{
			return this->valueToString() + " of " + this->handToString();
		}
};

