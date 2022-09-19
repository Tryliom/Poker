#pragma once
#include "../deck/card.h"

#include <string>
#include <vector>

class CardImage
{
private:
	std::vector<std::string> _image;
public:
	CardImage();
	explicit CardImage(const std::string& path);
	CardImage(const std::string& path, CardSuit suit);

	std::vector<std::string> GetImage() const { return this->_image; }
};
