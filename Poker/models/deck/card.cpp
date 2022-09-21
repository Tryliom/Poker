#include "card.h"

#include <codecvt>

Card::Card(const CardSuit suit, const CardValue value)
{
	this->_suit = suit;
	this->_value = value;
}

std::string Card::CardSuitToString(const CardSuit cardSuit)
{
	switch (cardSuit)
	{
		case CardSuit::CLUBS:
			return u8"♣";
		case CardSuit::HEARTS:
			return u8"♥";
		case CardSuit::SPADES:
			return u8"♠";
		case CardSuit::DIAMONDS:
			return u8"♦";
		case CardSuit::END:
			return "unknown";
	}

	return "unknown";
}

std::string Card::CardValueToString(const CardValue cardValue)
{
	switch (cardValue)
	{
		case CardValue::TWO:
			return "2";
		case CardValue::THREE:
			return "3";
		case CardValue::FOUR:
			return "4";
		case CardValue::FIVE:
			return "5";
		case CardValue::SIX:
			return "6";
		case CardValue::SEVEN:
			return "7";
		case CardValue::EIGHT:
			return "8";
		case CardValue::NINE:
			return "9";
		case CardValue::TEN:
			return "10";
		case CardValue::JACK:
			return "Jack";
		case CardValue::QUEEN:
			return "Queen";
		case CardValue::KING:
			return "King";
		case CardValue::ACE:
			return "Ace";
		case CardValue::END:
			return "Unknown";
	}

	return "Unknown";
}