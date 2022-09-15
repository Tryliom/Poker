#include "deck.h"

#include <random>

#include "../utility/utils.h"

const std::vector<CardSuit> HANDS = {CardSuit::CLUBS, CardSuit::DIAMONDS, CardSuit::HEARTS, CardSuit::SPADES};
const std::vector<CardValue> VALUES = { CardValue::TWO, CardValue::THREE, CardValue::FOUR, CardValue::FIVE, CardValue::SIX, CardValue::SEVEN, CardValue::EIGHT, CardValue::NINE, CardValue::TEN, CardValue::JACK, CardValue::QUEEN, CardValue::KING, CardValue::ACE };

Deck::Deck()
{
	// Loop in suits and values to insert every type of cards inside the deck
	for (int suit = static_cast<int>(CardSuit::CLUBS); suit < static_cast<int>(CardSuit::END); suit++)
	{
		for (int value = static_cast<int>(CardValue::TWO); value < static_cast<int>(CardValue::END); value++)
		{
			this->_cards.emplace_back(Card(static_cast<CardSuit>(suit), static_cast<CardValue>(value)));
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
