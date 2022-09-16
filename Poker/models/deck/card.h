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
	public:
		Card(CardSuit hand, CardValue value);

		/**
		 * \brief Return the card as a string
		 */
		explicit operator std::string() const
		{
			return CardValueToString(_value) + " of " + CardSuitToString(_suit);
		}

		CardSuit GetSuit() const { return this->_suit; }
		CardValue GetValue() const { return this->_value; }
		static std::string CardSuitToString(const CardSuit cardSuit);
		static std::string CardValueToString(const CardValue cardValue);
};

