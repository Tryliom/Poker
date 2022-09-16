#pragma once
#include "../deck/pattern/pattern.h"

#include <vector>

class Card;

class Player
{
private:
    std::string _name;
    std::vector<Card> _hand;
    Pattern _pattern;
    int _score;
public:
    explicit Player(const std::string& name);

	std::vector<Card> GetHand() const { return this->_hand; }
	void ClearHand() { this->_hand.clear(); }
	Pattern GetPattern() const { return this->_pattern; }
	std::string GetName() const { return this->_name; }
	int GetScore() const { return this->_score; }
	void IncrementScore() { this->_score++; }

    void AddCard(Card card);
	void CheckPattern();
};
