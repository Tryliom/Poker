#pragma once
#include "../card.h"

#include <vector>

enum class PatternType
{
	HIGHCARD,
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
public:
	Pattern();
	Pattern(const PatternType patternType, const std::vector<CardValue>& bestValues, CheckPriority checkPriority = CheckPriority::ORDER);
	Pattern(const PatternType patternType, const CardValue& bestValue, CheckPriority checkPriority = CheckPriority::ORDER);
	
	PatternType GetPatternType() const;
	std::vector<CardValue>  GetCardValue() const;
	bool IsBetter(const Pattern& other) const;
	static Pattern Check(const std::vector<Card>& cards);
};