#pragma once
#include <vector>

class Card;

class Player
{
private:
    std::vector<Card> _hand;

public:
    Player();

    std::vector<Card> GetHand() const;
    void AddCard(Card card);
};
