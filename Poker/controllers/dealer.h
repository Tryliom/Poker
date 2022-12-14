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
	CHOOSING_BET,
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
	/**
	 * \brief Assets containing all the card images
	 */
	Assets _assets;
	/**
	 * \brief The screen used to display the game
	 */
	Screen _screen;

	int _totalBet;
	/**
	 * \brief Distribute a number of card equal to START_CARD_PER_PLAYERS to each players unless the deck is empty
	 */
	void distributeCards();
public:
	Dealer();
	// Selected choice in a bet
	int SelectedChoice = 0;
	// The possible bets
	std::vector<int> Bets = {};
	// True if the user can press keys
	bool CanEnterKey = false;
	// The best players of the game
	std::vector<Player> BestPlayers = {};

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
	 * \brief Ask for the user to enter key and do things in it
	 */
	void WaitToEnterKey();
	/**
	 * \brief Set the status of the game
	 * \param status The new status of the game
	 */
	void SetStatus(const Status status) { this->_status = status; }
	/**
	 * \brief Get the status of the game
	 * \return The status of the game
	 */
	Status GetStatus() const { return this->_status; }
};

