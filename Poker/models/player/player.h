#pragma once
#include "../deck/pattern/pattern.h"

#include <vector>

class Card;

int constexpr BET_AMOUNT = 15;

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
    int _money;
    int _moneyDiff;
	HandStatus _handStatus;
public:
    Player(const std::string& name, int order);

	std::vector<Card> GetHand() const { return this->_hand; }
	void ClearHand() { this->_hand.clear(); }
	Pattern GetPattern() const { return this->_pattern; }
	std::string GetName() const { return this->_name; }
	int GetMoney() const { return this->_money; }
	void SubtractMoney(const int amount) { this->_money -= amount; }
	void AddMoney(const int amount) { this->_money += amount; }
    int GetBet() { SubtractMoney(BET_AMOUNT); return BET_AMOUNT; }
	int GetMoneyDiff() const { return this->_moneyDiff; }
	void ResetMoneyDiff() { this->_moneyDiff = 0; }
	void IncreaseMoneyDiff(const int amount) { this->_moneyDiff += amount; }
    void DecreaseMoneyDiff(const int amount) { this->_moneyDiff -= amount; }

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
