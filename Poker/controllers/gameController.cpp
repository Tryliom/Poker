#include "gameController.h"

GameController::GameController()
{
	this->_deck = Deck();
}	


void GameController::Start()
{
	
}

void GameController::Restart()
{
	this->_deck = Deck();
}

