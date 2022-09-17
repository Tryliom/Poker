#include "Pattern.h"

#include <algorithm>
#include <functional>
#include <ostream>

Pattern* Pattern::checkStraightFlush(std::vector<Card>& cards)
{
	const std::vector<Card> sequence = getSequence(cards, true);

	if (sequence.size() == 5)
	{
		return new Pattern(PatternType::STRAIGHT_FLUSH, getBestValue(sequence));
	}
		

    return nullptr;
}

Pattern* Pattern::checkFourOfAKind(const std::vector<Card>& cards)
{
	for (auto& card : cards)
	{
		const int total = countValue(cards, card.GetValue());

		if (total == 4)
		{
			return new Pattern(PatternType::FOUR_OF_A_KIND, card.GetValue());
		}
	}

    return nullptr;
}

Pattern* Pattern::checkFullHouse(const std::vector<Card>& cards)
{
	CardValue* threeOfAKindValue = nullptr;
	CardValue* pairValue = nullptr;

	for (auto& card : cards)
	{
		const int total = countValue(cards, card.GetValue());

		if (total == 3)
		{
			threeOfAKindValue = new CardValue(card.GetValue());
		}
		else if (total == 2)
		{
			pairValue = new CardValue(card.GetValue());
		}
	}

	if (threeOfAKindValue != nullptr && pairValue != nullptr)
	{
		return new Pattern(PatternType::FULL_HOUSE, { *threeOfAKindValue, *pairValue });
	}

    return nullptr;
}

Pattern* Pattern::checkFlush(const std::vector<Card>& cards)
{
	for (int i = 0; i < static_cast<int>(CardSuit::END); i++)
	{
		if (countSuit(cards, static_cast<CardSuit>(i)) == 5)
		{
			return new Pattern(PatternType::FLUSH, getBestValue(cards));
		}
	}

    return nullptr;
}

Pattern* Pattern::checkStraight(std::vector<Card>& cards)
{
	const std::vector<Card> sequence = getSequence(cards);

	if (sequence.size() == 5)
	{
		return new Pattern(PatternType::STRAIGHT, getBestValue(sequence));
	}

    return nullptr;
}

Pattern* Pattern::checkThreeOfAKind(const std::vector<Card>& cards)
{
	for (auto &card : cards)
	{
		const int total = countValue(cards, card.GetValue());

		if (total == 3)
		{
			return new Pattern(PatternType::THREE_OF_A_KIND, card.GetValue());
		}
	}

    return nullptr;
}

Pattern* Pattern::checkTwoPairs(const std::vector<Card>& cards)
{
	Pattern* pattern = nullptr;

	for (auto& card : cards)
	{
		const int total = Pattern::countValue(cards, card.GetValue());

		if (total == 2 && (pattern == nullptr || pattern->_bestValues.front() != card.GetValue()))
		{
			if (pattern != nullptr)
			{
				pattern->_bestValues = { card.GetValue(), pattern->_bestValues[0]};
				return pattern;
			}

			pattern = new Pattern(PatternType::TWO_PAIRS, card.GetValue());
		}
	}

    return nullptr;
}

Pattern* Pattern::checkPair(const std::vector<Card>& cards)
{
	for (auto& card : cards)
	{
		const int total = countValue(cards, card.GetValue());

		if (total == 2)
		{
			return new Pattern(PatternType::PAIR, card.GetValue());
		}
	}

    return nullptr;
}

Pattern* Pattern::checkHighCard(const std::vector<Card>& cards)
{
	return new Pattern(PatternType::HIGH_CARD, getBestValue(cards));
}

Pattern::Pattern()
{
	this->_patternType = PatternType::END;
	this->_bestValues = {CardValue::END};
}

Pattern::Pattern(const PatternType patternType, const std::vector<CardValue>& bestValues)
{
	this->_patternType = patternType;
	this->_bestValues = bestValues;
}

Pattern::Pattern(const PatternType patternType, const CardValue& bestValue)
{
	this->_patternType = patternType;
	this->_bestValues = { bestValue };
}

PatternType Pattern::GetPatternType() const
{
	return this->_patternType;
}

std::vector<CardValue> Pattern::GetCardValue() const
{
	return this->_bestValues;
}

Pattern Pattern::Check(std::vector<Card>& cards)
{
	const std::vector<std::function<Pattern*(std::vector<Card>&)>> checks = {
    	Pattern::checkStraightFlush,
		Pattern::checkFourOfAKind,
		Pattern::checkFullHouse,
		Pattern::checkFlush,
		Pattern::checkStraight,
		Pattern::checkThreeOfAKind,
		Pattern::checkTwoPairs,
		Pattern::checkPair
    };

	for (auto &check : checks)
	{
		Pattern* pattern = check(cards);
		if (pattern != nullptr)
		{
			return *pattern;
		}
	}

	return *Pattern::checkHighCard(cards);
}

std::string Pattern::patternTypeToString() const
{
    switch (this->_patternType)
    {
		case PatternType::STRAIGHT_FLUSH:
			return "Straight Flush";
		case PatternType::FOUR_OF_A_KIND:
			return "Four of a Kind";
		case PatternType::FULL_HOUSE:
			return "Full House";
		case PatternType::FLUSH:
			return "Flush";
		case PatternType::STRAIGHT:
			return "Straight";
		case PatternType::THREE_OF_A_KIND:
			return "Three of a Kind";
		case PatternType::TWO_PAIRS:
			return "Two Pairs";
		case PatternType::PAIR:
			return "Pair";
		case PatternType::HIGH_CARD:
			return "High Card";
	    case PatternType::END:
	        return "Unknown";
    }

    return "Unknown";
}

int Pattern::countValue(const std::vector<Card>& cards, const CardValue value)
{
	int total = 0;

	for (auto& card : cards)
	{
		if (card.GetValue() == value)
		{
			total++;
		}
	}

	return total;
}

std::vector<Card> Pattern::getSequence(const std::vector<Card>& cards, const bool sameSuit)
{
	std::vector<Card> bestSequence;
	std::vector<Card> sequence;
	bool follow = false;
	CardValue value = cards.at(0).GetValue();

	for (int i = 1; i < static_cast<int>(cards.size()); i++)
	{
		auto nextValue = static_cast<CardValue>(static_cast<int>(value) + 1);
		if (nextValue == CardValue::END)
		{
			nextValue = CardValue::TWO;
		}

		if (nextValue != cards.at(i).GetValue() || sameSuit && cards.at(i).GetSuit() != cards.at(i - 1).GetSuit())
		{
			if (follow && sequence.size() > bestSequence.size())
			{
				bestSequence = sequence;
			}
			sequence = {};
			follow = false;
		}
		else
		{
			value = cards.at(i).GetValue();
			sequence.emplace_back(cards.at(i));
			follow = true;
		}
	}

	if (sequence.size() > bestSequence.size())
	{
		bestSequence = sequence;
	}

	return bestSequence;
}

CardValue Pattern::getBestValue(const std::vector<Card>& cards)
{
	CardValue bestValue = cards[0].GetValue();

	for (auto& card : cards)
	{
		if (card.GetValue() > bestValue)
		{
			bestValue = card.GetValue();
		}
	}

	return bestValue;
}

int Pattern::countSuit(const std::vector<Card>& cards, const CardSuit suit)
{
	int total = 0;

	for (auto& card : cards)
	{
		if (card.GetSuit() == suit)
		{
			total++;
		}
	}

	return total;
}
