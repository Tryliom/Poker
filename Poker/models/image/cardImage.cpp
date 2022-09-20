#include "CardImage.h"

#include <fstream>
#include <iostream>
#include <regex>

CardImage::CardImage()
{
	_image = {};
}

CardImage::CardImage(const std::string& path)
{
	_image = {};
	std::ifstream file(path);
	std::string line;

	while (std::getline(file, line))
	{
		_image.emplace_back(line);
	}
}

CardImage::CardImage(const std::string& path, const CardSuit suit)
{
	_image = {};
	std::ifstream file(path);
	std::string line;
	const std::string symbol = Card::CardSuitToString(suit);

	while (std::getline(file, line))
	{
		// Replace all § by the symbol
		line = std::regex_replace(line, std::regex(u8"§"), symbol);
		//line = std::regex_replace(line, std::regex(u8"§"), "O");
		_image.emplace_back(line);
	}
}
