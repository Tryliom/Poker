#include "gameController.h"

#include <iostream>

GameController::GameController()
{
	this->_deck = Deck();
}	


void GameController::Start()
{
	std::cout << static_cast<std::string>(this->_deck) << std::endl;
}

void GameController::Restart()
{
	this->_deck = Deck();
}

