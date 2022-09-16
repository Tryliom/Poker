#pragma once
#include "../card.h"

#include <vector>

enum class PatternType
{
	HIGH_CARD,
	PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH,
	END
};

enum class CheckPriority
{
	ORDER,
	NO_ORDER
};

class Pattern
{
private:
	PatternType _patternType;
	std::vector<CardValue> _bestValues;
	CheckPriority _checkPriority;

	// Type of pattern to check
	static Pattern* checkStraightFlush(std::vector<Card>& cards);
	static Pattern* checkFourOfAKind(const std::vector<Card>& cards);
	static Pattern* checkFullHouse(const std::vector<Card>& cards);
	static Pattern* checkFlush(const std::vector<Card>& cards);
	static Pattern* checkStraight(std::vector<Card>& cards);
	static Pattern* checkThreeOfAKind(const std::vector<Card>& cards);
	static Pattern* checkTwoPairs(const std::vector<Card>& cards);
	static Pattern* checkPair(const std::vector<Card>& cards);
	static Pattern* checkHighCard(const std::vector<Card>& cards);

	static int countValue(const std::vector<Card>& cards, CardValue value);
	static int countSuit(const std::vector<Card>& cards, CardSuit suit);
	static void sortCards(std::vector<Card>& cards);
	static std::vector<Card> getSequence(const std::vector<Card>& cards, bool sameSuit = false);
	static CardValue getBestValue(const std::vector<Card>& cards);
	std::string patternTypeToString() const;
public:
	Pattern();
	Pattern(const PatternType patternType, const std::vector<CardValue>& bestValues, const CheckPriority checkPriority = CheckPriority::ORDER);
	Pattern(const PatternType patternType, const CardValue& bestValue, const CheckPriority checkPriority = CheckPriority::ORDER);
	
	PatternType GetPatternType() const;
	std::vector<CardValue>  GetCardValue() const;
	
	static Pattern Check(std::vector<Card>& cards);

	/**
	 * \brief Return the pattern as string
	 */
	explicit operator std::string() const
	{
		std::string values;

		for (auto& value : this->_bestValues)
		{
			if (!values.empty())
			{
				values += ", ";
			}
			values += Card::CardValueToString(value);
		}

		return patternTypeToString() + " (" + values + ")";
	}

	/**
	 * \brief Check if the pattern has the same value as another
	 * \param other The other pattern to compare
	 * \return True if the pattern has the same value as the other
	 */
	bool operator==(const Pattern& other) const
	{
		if (this->_patternType == other._patternType)
		{
			int maxValue1 = 0;
			int maxValue2 = 0;

			for (int i = 0; i < static_cast<int>(this->_bestValues.size()); i++)
			{
				maxValue1 += static_cast<int>(this->_bestValues.at(i));
				maxValue2 += static_cast<int>(other._bestValues.at(i));
			}

			return maxValue1 == maxValue2;
		}

		return false;
	}

	/**
	 * \brief Check if the pattern has a different value than another
	 * \param other The other pattern to compare
	 * \return True if the pattern has a different value than the other
	 */
	bool operator!=(const Pattern& other) const
	{
		return !(*this == other);
	}

	/**
	 * \brief Check if this pattern has a better value than another
	 * \param other The other pattern to compare
	 * \return True if this pattern has a better value than the other
	 */
	bool operator>(const Pattern& other) const
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

			return false;
		}

		return this->_patternType > other._patternType;
	}
};
