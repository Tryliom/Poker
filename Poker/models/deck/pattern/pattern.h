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

/**
 * \brief Define a poker pattern (e.g. pair, straight, flush, etc.)
 */
class Pattern
{
private:
	PatternType _patternType;
	std::vector<CardValue> _bestValues;

	// Type of pattern to check
	/**
	 * \brief Check if the cards form a straight flush: 5 cards of the same suit in sequence
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkStraightFlush(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a four of a kind: 4 cards of the same value
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkFourOfAKind(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a full house: 3 cards of the same value and 2 cards of the same value
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkFullHouse(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a flush: 5 cards of the same suit
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkFlush(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a straight: 5 cards in sequence of any suit
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkStraight(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a three of a kind: 3 cards of the same value
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkThreeOfAKind(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a two pairs: 2 times 2 cards of the same value
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkTwoPairs(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a pair: 2 cards of the same value
	 * \param cards The cards to check
	 * \return The pattern if found, nullptr otherwise
	 */
	static Pattern* checkPair(const std::vector<Card>& cards);
	/**
	 * \brief Check if the cards form a high card: the highest card value
	 * \param cards The cards to check
	 * \return The pattern, always found
	 */
	static Pattern* checkHighCard(const std::vector<Card>& cards);

	// Utility for pattern check
	/**
	 * \brief Count the number of cards with the same value
	 * \param cards The cards to check
	 * \param value The value wanted to count
	 * \return The number of cards with the same value
	 */
	static int countValue(const std::vector<Card>& cards, CardValue value);
	/**
	 * \brief Count the number of cards with the same suit
	 * \param cards The cards to check
	 * \param suit The suit wanted to count
	 * \return The number of cards with the same suit
	 */
	static int countSuit(const std::vector<Card>& cards, CardSuit suit);
	/**
	 * \brief Get a sequence of cards that are consecutive
	 * \param cards The cards to check
	 * \param sameSuit If the cards must have the same suit
	 * \return The sequence of cards that are consecutive, the last card is the highest
	 */
	static std::vector<Card> getSequence(const std::vector<Card>& cards, bool sameSuit = false);
	/**
	 * \brief Get the highest card value of a list of cards
	 * \param cards The cards to check
	 * \return The highest card value
	 */
	static CardValue getBestValue(const std::vector<Card>& cards);
	/**
	 * \brief Get a list of card values sorted by their card value
	 * \param cards The cards to check
	 * \param excludedValues The values to exclude from the list
	 * \return A list of the best card values
	 */
	static std::vector<CardValue> getBestValues(const std::vector<Card>& cards, const std::vector<CardValue>& excludedValues = {});
	/**
	 * \brief Convert a pattern type to a string
	 * \return The string representation of the pattern type
	 */
	std::string patternTypeToString() const;
public:
	Pattern();
	Pattern(PatternType patternType, const std::vector<CardValue>& bestValues);
	Pattern(PatternType patternType, const CardValue& bestValue);
	
	PatternType GetPatternType() const { return this->_patternType; }
	std::vector<CardValue> GetCardValue() const { return this->_bestValues; }
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
			// Check if the best values are the same
			for (int i = 0; i < static_cast<int>(this->_bestValues.size()); i++)
			{
				if (this->_bestValues.at(i) != other._bestValues.at(i))
				{
					return false;
				}
			}

			return true;
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
			// Check if the best values are better
			for (int i = 0; i < static_cast<int>(this->_bestValues.size()); i++)
			{
				if (this->_bestValues.at(i) == other._bestValues.at(i))
				{
					continue;
				}

				return this->_bestValues.at(i) > other._bestValues.at(i);
			}
			
			return false;
		}

		return this->_patternType > other._patternType;
	}
};
