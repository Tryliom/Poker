#pragma once
#include "../models/deck/deck.h"

int constexpr NB_PLAYER = 5;
int constexpr START_CARD_PER_PLAYERS = 5;

class GameController
{
private:
	Deck _deck;
public:
	GameController();
	void Start();
	void Restart();
};

