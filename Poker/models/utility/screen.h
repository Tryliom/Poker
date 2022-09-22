#pragma once
#include "../image/cardImage.h"

#include <string>
#include <vector>

struct Text
{
	std::string Str{};
	int X{ 0 };
	int Y{ 0 };
	bool XCentered{ false };
};

class Screen
{
private:
	std::vector<std::vector<std::string>> _screen;
	int _height;
	int _width;

	static void setPos(const int x, const int y);
public:
	Screen();

	void Clear();

	void Render() const;

	void Draw(Text text);

	void DrawImage(const CardImage& image, int x, int y);

	int GetHeight() const { return this->_height; }
	int GetWidth() const { return this->_width; }
};

