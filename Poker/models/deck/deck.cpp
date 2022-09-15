#include "deck.h"

#include <random>

#include "../utility/utils.h"

const std::vector<Suit> HANDS = {Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES};
const std::vector<Value> VALUES = { Value::TWO, Value::THREE, Value::FOUR, Value::FIVE, Value::SIX, Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN, Value::JACK, Value::QUEEN, Value::KING, Value::ACE };

Deck::Deck()
{
	// Loop in suits and values to insert every type of cards inside the deck
	for (int suit = static_cast<int>(Suit::CLUBS); suit < static_cast<int>(Suit::END); suit++)
	{
		for (int value = static_cast<int>(Value::TWO); value < static_cast<int>(Value::END); value++)
		{
			this->_cards.emplace_back(Card(static_cast<Suit>(suit), static_cast<Value>(value)));
		}
	}
}

Card Deck::PickRandomCard()
{
	// Get a random int between 0 and the size of the deck
	std::shuffle(this->_cards.begin(), this->_cards.end(), std::random_device());
	// Get a card from the back of the list
	const Card card = this->_cards.back();
	// Remove the card from the deck
	Utils::Remove(this->_cards, card);

	return card;
}

bool Deck::IsEmpty() const
{
    return this->_cards.empty();
}
