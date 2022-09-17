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
		Card(CardSuit suit, CardValue value);

		/**
		 * \brief Return the card as a string
		 */
		explicit operator std::string() const
		{
			return CardValueToString(_value) + " " + CardSuitToString(_suit);
		}

		CardSuit GetSuit() const { return this->_suit; }
		CardValue GetValue() const { return this->_value; }
		/**
		 * \brief Convert a CardSuit to a string
		 * \param cardSuit The CardSuit to convert
		 * \return The string representation of the CardSuit
		 */
		static std::string CardSuitToString(const CardSuit cardSuit);
		/**
		 * \brief Convert a CardValue to a string
		 * \param cardValue The CardValue to convert
		 * \return The string representation of the CardValue
		 */
		static std::string CardValueToString(const CardValue cardValue);
};

