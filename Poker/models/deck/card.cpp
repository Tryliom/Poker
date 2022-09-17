#include "card.h"

#include <codecvt>

/**
 * \brief This function come from https://mariusbancila.ro/blog/2019/05/16/cpp-is-fun/ \n
 * It converts a utf16 string to a utf8 string, used to convert emojis
 * \param utf16String The utf16 string to convert
 * \return The utf8 string
 */
std::string utf16_to_utf8(const std::u16string& utf16String)
{
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t*>(utf16String.data());
	return convert.to_bytes(p, p + utf16String.size());
}

Card::Card(const CardSuit suit, const CardValue value)
{
	this->_suit = suit;
	this->_value = value;
}

std::string Card::CardSuitToString(CardSuit cardSuit)
{
	switch (cardSuit)
	{
		case CardSuit::CLUBS:
			return utf16_to_utf8(u"♣");
		case CardSuit::HEARTS:
			return utf16_to_utf8(u"♥");
		case CardSuit::SPADES:
			return utf16_to_utf8(u"♠");
		case CardSuit::DIAMONDS:
			return utf16_to_utf8(u"♦");
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