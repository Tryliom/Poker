#include "screen.h"

#include <chrono>
#include <codecvt>
#include <iostream>
#include <ostream>
#include <thread>
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
	
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(output, &cursorInfo);
	// set the cursor visibility
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(output, &cursorInfo);

	for (int h = 0; h < _height; h++)
	{
		std::string row;
		for (int w = 0; w < _width; w++)
		{
			if (w == 0 || w == _width - 1 || h == 0 || h == _height - 1)
			{
				row += "#";
			}
			else
			{
				row += " ";
			}
		}

		this->_screen.emplace_back(row);
	}
}

void Screen::Render() const
{
	for (int h = 0; h < _height; h++)
	{
		// for (int w = 0; w < _width; w++)
		// {
		// 	this->setPos(w, h);
		// 	std::cout << this->_screen[h][w];
		// }
		this->setPos(0, h);
		std::cout << this->_screen[h];
	}
}

void Screen::Draw(const std::string& str, const int x, const int y)
{
	if (_height <= y || _width <= x)
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(str.length()); i++)
	{
		if (x + i >= _width)
		{
			break;
		}
		
		this->_screen[y][x + i] = str[i];
	}
}

void Screen::DrawImage(const CardImage& image, const int x, int y)
{
	for (const std::string& str : image.GetImage())
	{
		this->Draw("\t " + str, x, y);
		y++;
	}
}
