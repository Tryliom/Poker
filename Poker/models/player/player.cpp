#include "player.h"
#include "../deck/card.h"

Player::Player()
{
    this->_hand = {};
}

std::vector<Card> Player::GetHand() const
{
    return this->_hand;
}

void Player::AddCard(Card card)
{
    this->_hand.emplace_back(card);
}
