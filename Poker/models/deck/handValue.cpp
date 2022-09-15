#include "HandValue.h"

HandValue::HandValue(const HandType handType, const CardValue higherSuit)
{
	this->_handType = handType;
	this->_higherSuit = higherSuit;
}

bool HandValue::IsBetter(const HandValue other) const
{
	if (this->_handType > other._handType)
	{
		return true;
	}
	else if (this->_handType == other._handType)
	{
		return this->_higherSuit > other._higherSuit;
	}

	return false;
}
