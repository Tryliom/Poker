#pragma once
#include "../deck/pattern/pattern.h"

#include <vector>

class Card;

class Player
{
private:
    std::vector<Card> _hand;
    Pattern _handValue;
public:
    Player();

    std::vector<Card> GetHand() const;
    void AddCard(Card card);
	void SetHandValue(const Pattern& handValue);
};
