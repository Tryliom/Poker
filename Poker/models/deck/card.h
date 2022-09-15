#pragma once
#include <string>

enum class CardSuit {
	CLUBS, HEARTS, SPADES, DIAMONDS, END
};

enum class CardValue
{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, END
};

class Card
{
	private:
		CardSuit _suit;
		CardValue _value;

		std::string handToString() const;
		std::string valueToString() const;
	public:
		Card(CardSuit hand, CardValue value);

		/**
		 * \brief Return the card as a string
		 */
		explicit operator std::string() const
		{
			return this->valueToString() + " of " + this->handToString();
		}

		CardSuit GetSuit() const;
		CardValue GetValue() const;
};

