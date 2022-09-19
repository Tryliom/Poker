#include "deck.h"
#include "pattern/Pattern.h"

#include <random>

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

void Deck::Shuffle()
{
	std::shuffle(this->_cards.begin(), this->_cards.end(), std::random_device());
}

Card Deck::PickACard()
{
	// Pick a card from the top of the deck
	const Card card = this->_cards.front();
	// Remove the card from the deck
	this->_cards.erase(this->_cards.begin());

	return card;
}

bool Deck::IsEmpty() const
{
    return this->_cards.empty();
}
