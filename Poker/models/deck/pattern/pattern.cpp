#include "Pattern.h"

#include <iostream>
#include <map>
#include <ostream>

Pattern::Pattern()
{
	this->_patternType = PatternType::END;
	this->_bestValues = {CardValue::END};
}

Pattern::Pattern(const PatternType patternType, const std::vector<CardValue>& bestValues, CheckPriority checkPriority)
{
	this->_patternType = patternType;
	this->_bestValues = bestValues;
	this->_checkPriority = checkPriority;
}

Pattern::Pattern(const PatternType patternType, const CardValue& bestValue, CheckPriority checkPriority)
{
	this->_patternType = patternType;
	this->_bestValues = { bestValue };
	this->_checkPriority = checkPriority;
}

bool Pattern::IsBetter(const Pattern& other) const
{
	if (this->_patternType == other._patternType)
	{
		for (int i = 0; i < static_cast<int>(this->_bestValues.size()); i++)
		{
			if (this->_bestValues.at(i) > other._bestValues.at(i))
			{
				return true;
			}
		}
		//TODO: Return an enum in order to count a draw
		return false;
	}

	return this->_patternType > other._patternType;
}

PatternType Pattern::GetPatternType() const
{
	return this->_patternType;
}

std::vector<CardValue> Pattern::GetCardValue() const
{
	return this->_bestValues;
}

Pattern Check(std::vector<Card>& cards)
{
	//TODO: Check in PatternType reverse order for all types

    std::map<CardValue, int> sameCardValue = {};
    std::map<CardSuit, int> sameCardSuit = {};
    std::map<CardSuit, std::map<CardValue, int>> sortedCards = {};
    std::vector<CardValue> pair = {};
    Pattern pattern;


    for (Card card : cards)
    {
        if (sameCardValue.find(card.GetValue()) != sameCardValue.end())
        {
            sameCardValue[card.GetValue()] = 0;
        }
        sameCardValue[card.GetValue()]++;

        if (sameCardSuit.find(card.GetSuit()) != sameCardSuit.end())
        {
            sameCardSuit[card.GetSuit()] = 0;
        }
        sameCardSuit[card.GetSuit()]++;

        if (sortedCards.find(card.GetSuit()) != sortedCards.end())
        {
            sortedCards[card.GetSuit()] = {};
        }

        if (sortedCards[card.GetSuit()].find(card.GetValue()) != sortedCards[card.GetSuit()].end())
        {
            sortedCards[card.GetSuit()][card.GetValue()] = 0;
        }
        sortedCards[card.GetSuit()][card.GetValue()]++;
    }


    for (const auto& element : sameCardValue)
    {
        std::cout << static_cast<int>(element.first) << " " << static_cast<int>(element.second) << std::endl;

        if (element.second == 4)
        {
            pattern = Pattern(PatternType::FOUR_OF_A_KIND, element.first);
        }
        else if (element.second == 3)
        {
            if (pattern.GetPatternType() == PatternType::PAIR)
            {
                pattern = Pattern(PatternType::FULL_HOUSE, { element.first , pattern.GetCardValue().front() });
            }
            else
            {
                pattern = Pattern(PatternType::THREE_OF_A_KIND, element.first);
            }
        }
        else if (element.second == 2)
        {
            if (pattern.GetPatternType() == PatternType::THREE_OF_A_KIND)
            {
                pattern = Pattern(PatternType::FULL_HOUSE, { pattern.GetCardValue().front(), element.first });
            }
            else if (pattern.GetPatternType() == PatternType::PAIR)
            {
                pattern = Pattern(PatternType::TWO_PAIRS, { pattern.GetCardValue().front(), element.first });
            }
            else
            {
                pattern = Pattern(PatternType::PAIR, element.first, CheckPriority::NO_ORDER);
            }
        }
    }


	return Pattern();
}