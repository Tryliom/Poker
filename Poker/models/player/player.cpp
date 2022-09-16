#include "player.h"
#include "../deck/card.h"
#include "../deck/pattern/pattern.h"

Player::Player(const std::string& name)
{
	this->_name = name;
    this->_hand = {};
	this->_pattern = Pattern();
	this->_score = 0;
}

void Player::AddCard(Card card)
{
    this->_hand.emplace_back(card);
}

void Player::CheckPattern()
{
	this->_pattern = Pattern::Check(this->_hand);
}
