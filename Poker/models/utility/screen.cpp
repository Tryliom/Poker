#include "screen.h"

#include <iostream>
#include <ostream>
#include <windows.h>

void Screen::setPos(const int x, const int y)
{
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

Screen::Screen()
{
	this->_height = 0;
	this->_width = 0;
	this->_screen = {};
}

void Screen::Clear()
{
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(output, &csbi);
	this->_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	this->_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	this->_screen = {};
	

	for (int h = 0; h < _height; h++)
	{
		std::string row;
		for (int w = 0; w < _width; w++)
		{
			row += " ";
		}

		this->_screen.emplace_back(row);
	}
}

void Screen::Render() const
{
	this->setPos(0, 0);
	for (int h = 0; h < _height; h++)
	{
		this->setPos(0, h);
		std::cout << this->_screen[h];
	}
}

void Screen::Draw(const std::string& str, const int x, const int y)
{
	for (int i = 0; i < static_cast<int>(str.length()); i++)
	{
		if (static_cast<int>(this->_screen[y].length()) > x + i)
		{
			this->_screen[y][x + i] = str[i];
		}
	}
}
