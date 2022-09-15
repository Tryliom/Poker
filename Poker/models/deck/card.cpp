#include "card.h"

#include <iostream>

Card::Card(const Hand hand, const Value value)
{
	this->_hand = hand;
	this->_value = value;
}

std::string Card::handToString() const
{
	switch (this->_hand)
	{
		case Hand::CLUBS:
			return "clubs";
		case Hand::HEARTS:
			return "hearts";
		case Hand::SPADES:
			return "spades";
		case Hand::SQUARES:
			return "squares";
		case Hand::ENUM_END:
			return "unknown";
	}

	return "Unknown";
}

std::string Card::valueToString() const
{
	switch (this->_value)
	{
		case Value::TWO:
			return "2";
		case Value::THREE:
			return "3";
		case Value::FOUR:
			return "4";
		case Value::FIVE:
			return "5";
		case Value::SIX:
			return "6";
		case Value::SEVEN:
			return "7";
		case Value::EIGHT:
			return "8";
		case Value::NINE:
			return "9";
		case Value::TEN:
			return "10";
		case Value::JACK:
			return "Jack";
		case Value::QUEEN:
			return "Queen";
		case Value::KING:
			return "King";
		case Value::ACE:
			return "Ace";
		case Value::ENUM_END:
			return "Unknown";
	}

	return "Unknown";
}



std::string Card::ToString() const
{
	return this->valueToString() + " of " + this->handToString();
}
