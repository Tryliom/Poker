#pragma once
#include "../models/utility/Screen.h"
#include "../models/deck/deck.h"
#include "../models/player/player.h"
#include "../models/image/assets.h"

class Player;
int constexpr NB_PLAYER = 5;
int constexpr START_CARD_PER_PLAYERS = 5;

enum class Status
{
	START,
	DISPLAY_RESULTS,
	WAITING,
};

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
	 * \brief The current status of the game
	 */
	Status _status;

	Assets _assets;

	/**
	 * \brief Screen utility
	 */
	Screen _screen;

	/**
	 * \brief Distribute a number of card equal to START_CARD_PER_PLAYERS to each players unless the deck is empty
	 */
	void distributeCards();
public:
	Dealer();
	/**
	 * \brief Update the game
	 */
	void Update();
	/**
	 * \brief Call every ticks to update the game
	 */
	void OnTick();
	/**
	 * \brief Start a new game
	 */
	void StartAGame();
	/**
	 * \brief Set the status of the game
	 * \param status The new status of the game
	 */
	void SetStatus(const Status status) { this->_status = status; }
};

