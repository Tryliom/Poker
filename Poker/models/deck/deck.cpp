#include "deck.h"
#include "../utility/utils.h"

constexpr int HAND_SIZE = 5;
const std::vector<Hand> HANDS = {Hand::CLUBS, Hand::SQUARES, Hand::HEARTS, Hand::SPADES};
const std::vector<Value> VALUES = { Value::TWO, Value::THREE, Value::FOUR, Value::FIVE, Value::SIX, Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN, Value::JACK, Value::QUEEN, Value::KING, Value::ACE };

Deck::Deck()
{
	this->_cards = {};
	for (int hand = static_cast<int>(Hand::CLUBS); hand < static_cast<int>(Hand::ENUM_END); hand++)
	{
		for (int value = static_cast<int>(Value::TWO); value < static_cast<int>(Value::ENUM_END); value++)
		{
			this->_cards.emplace_back(Card(static_cast<Hand>(hand), static_cast<Value>(value)));
		}
	}
}

Card Deck::PickRandomCard()
{
	int randomIndex = Utils::GetRandomInt(0, static_cast<int>(this->_cards.size()) - 1);
	Card card = this->_cards[randomIndex];
	//TODO: Remove card from deck
	return card;
}

std::string Deck::ToString() const
{
	std::string result = "This deck contains " + std::to_string(this->_cards.size()) + " cards:";

	for (Card card : this->_cards)
	{
		result += "\n" + card.ToString();
	}

	return result;
}
