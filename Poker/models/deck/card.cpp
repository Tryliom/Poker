#include "card.h"

#include <iostream>

Card::Card(const CardSuit hand, const CardValue value)
{
	this->_hand = hand;
	this->_value = value;
}

std::string Card::handToString() const
{
	switch (this->_hand)
	{
		case CardSuit::CLUBS:
			return "clubs";
		case CardSuit::HEARTS:
			return "hearts";
		case CardSuit::SPADES:
			return "spades";
		case CardSuit::DIAMONDS:
			return "diamonds";
		case CardSuit::END:
			return "unknown";
	}

	return "Unknown";
}

std::string Card::valueToString() const
{
	switch (this->_value)
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