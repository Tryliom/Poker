#include "player.h"

#include <algorithm>

#include "../deck/card.h"
#include "../deck/pattern/pattern.h"

Player::Player(const std::string& name, const int order)
{
	this->_name = name;
    this->_hand = {};
	this->_pattern = Pattern();
	this->_score = 0;
	this->_order = order;
}

void Player::AddCard(Card card)
{
    this->_hand.emplace_back(card);
}

void Player::CheckPattern()
{
	// Sort his cards
	std::sort(_hand.begin(), _hand.end(), [](const Card& a, const Card& b) {
		return a.GetValue() < b.GetValue();
	});
	// Check what the best pattern he have
	this->_pattern = Pattern::Check(this->_hand);
}
