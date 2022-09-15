#pragma once
#include "../models/deck/deck.h"

int constexpr NB_PLAYER = 5;
int constexpr START_CARD_PER_PLAYERS = 5;

class GameController
{
private:
	/**
	 * \brief The whole deck used for a game
	 */
	Deck _deck;
public:
	GameController();
	/**
	 * \brief Start the game
	 */
	void Start();
	/**
	 * \brief Restart the game, reset the deck and all other attribute used in the game
	 */
	void Restart();
};

