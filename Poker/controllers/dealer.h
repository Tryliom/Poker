#pragma once
#include "../models/deck/deck.h"
#include "../models/player/player.h"
#include "../models/deck/pattern/pattern.h"

class Player;
int constexpr NB_PLAYER = 5;
int constexpr START_CARD_PER_PLAYERS = 5;

class Dealer
{
private:
	/**
	 * \brief The whole deck used for a game
	 */
	Deck _deck;
    /**
     * \brief The players of the game
     */
    std::vector<Player> _players;

	/**
	 * \brief Distribute a number of card equal to START_CARD_PER_PLAYERS to each players unless the deck is empty
	 */
	void distributeCards();

	Pattern getPattern(const std::vector<Card>& cards);
public:
	Dealer();
	/**
	 * \brief Start the game
	 */
	void Start();
	/**
	 * \brief Restart the game, reset the deck and all players
	 */
	void Restart();
};
