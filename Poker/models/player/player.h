#pragma once
#include "../deck/pattern/pattern.h"

#include <vector>

class Card;

enum class HandStatus
{
	HIDDEN,
	SHOWING,
};

class Player
{
private:
    std::string _name;
    std::vector<Card> _hand;
    Pattern _pattern;
    int _score;
	// Order used to sort players when they have the same pattern
	int _order;
	HandStatus _handStatus;
public:
    Player(const std::string& name, int order);

	std::vector<Card> GetHand() const { return this->_hand; }
	void ClearHand() { this->_hand.clear(); }
	Pattern GetPattern() const { return this->_pattern; }
	std::string GetName() const { return this->_name; }
	int GetScore() const { return this->_score; }
	void IncrementScore() { this->_score++; }
	int GetOrder() const { return this->_order; }

    /**
	 * \brief Throw away all the cards in the hand
     */
    void ThrowCardsAway();

    /**
	 * \brief Add a card to the player's hand
	 * \param card {Card} The card to add
     */
    void AddCard(Card card);
    /**
	 * \brief The player look at his hand and check the best pattern he have
     */
    void CheckPattern();
    /**
     * \brief The player sort his hand by value
     */
    void SortHand();

	void SetHandStatus(const HandStatus status) { this->_handStatus = status; }
	HandStatus GetHandStatus() const { return this->_handStatus; }
};
