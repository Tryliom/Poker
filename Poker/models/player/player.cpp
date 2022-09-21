#include "player.h"
#include "../deck/card.h"
#include "../deck/pattern/pattern.h"

#include <algorithm>

Player::Player(const std::string& name, const int order)
{
	this->_name = name;
    this->_hand = {};
	this->_pattern = Pattern();
	this->_money = 150;
	this->_moneyDiff = 0;
	this->_handStatus = HandStatus::HIDDEN;
}

void Player::ThrowCardsAway()
{
	_hand = {};
	_pattern = Pattern();
	_handStatus = HandStatus::HIDDEN;
}

void Player::AddCard(Card card)
{
    this->_hand.emplace_back(card);
}

void Player::CheckPattern()
{
	// Check what the best pattern he have
	this->_pattern = Pattern::Check(this->_hand);
}

void Player::SortHand()
{
	// Sort his cards
	std::sort(_hand.begin(), _hand.end(), [](const Card& a, const Card& b) {
		return a.GetValue() < b.GetValue();
	});
}
