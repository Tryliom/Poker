#include "deck.h"
#include "../utility/utils.h"

constexpr int HAND_SIZE = 5;
const std::vector<Suit> HANDS = {Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES};
const std::vector<Value> VALUES = { Value::TWO, Value::THREE, Value::FOUR, Value::FIVE, Value::SIX, Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN, Value::JACK, Value::QUEEN, Value::KING, Value::ACE };

Deck::Deck()
{
	this->_cards = {};
	for (int hand = static_cast<int>(Suit::CLUBS); hand < static_cast<int>(Suit::END); hand++)
	{
		for (int value = static_cast<int>(Value::TWO); value < static_cast<int>(Value::END); value++)
		{
			this->_cards.emplace_back(Card(static_cast<Suit>(hand), static_cast<Value>(value)));
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