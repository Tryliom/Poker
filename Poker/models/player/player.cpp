#include "player.h"
#include "../deck/card.h"
#include "../deck/pattern/pattern.h"

Player::Player()
{
    this->_hand = {};
	this->_handValue = Pattern();
}

std::vector<Card> Player::GetHand() const
{
    return this->_hand;
}

void Player::AddCard(Card card)
{
    this->_hand.emplace_back(card);
}

void Player::SetHandValue(const Pattern& handValue)
{
	this->_handValue = handValue;
}
