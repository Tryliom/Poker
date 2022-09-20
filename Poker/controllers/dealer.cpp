#include "Dealer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

int constexpr NAME_WIDTH = 20;
int constexpr TEXT_Y_OFFSET = 4;
int constexpr CARD_WIDTH = 12;
int constexpr CARD_HEIGHT = 9;

Dealer::Dealer()
{
	this->_deck = Deck();
    for (int i = 0; i < NB_PLAYER; i++)
    {
		this->_players.emplace_back(Player("Player " + std::to_string(i), i));
    }
	this->_status = Status::START;
}

void Dealer::OnTick()
{
    _screen.Clear();
	this->Update();
    _screen.Render();
}

void Dealer::Update()
{
    int y = 1;

    for (int i = 0; i < NB_PLAYER; i++)
    {
        int x = 2;
	    Player& player = this->_players[i];
    	std::string name = player.GetName() + " (" + std::to_string(player.GetScore()) + "p)";

        // Crash here
		_screen.Draw(name, x, y + TEXT_Y_OFFSET);
		x += NAME_WIDTH;

    	for (const Card &card : player.GetHand())
    	{
            if (player.GetHandStatus() == HandStatus::HIDDEN)
            {
				_screen.DrawImage(_assets.GetHiddenCard(), x, y);
            }
            else
            {
                _screen.DrawImage(_assets.GetCard(card), x, y);
            }

			x += CARD_WIDTH + 3;
    	}

    	if (player.GetPattern().GetPatternType() != PatternType::END) {
			_screen.Draw(static_cast<std::string>(player.GetPattern()), x, y + TEXT_Y_OFFSET);
			x += NAME_WIDTH;
    	}

        if (_status == Status::DISPLAY_RESULTS)
        {
            // Display results, the place of the player
            _screen.Draw(std::to_string(i + 1) + ((i + 1) == 1 ? "st" : "th") + " place", x, y + TEXT_Y_OFFSET);
        }

        y += CARD_HEIGHT + 1;
    }


    if (_status == Status::WAITING)
    {
		_screen.Draw("Press Enter to continue or any other key to stop", 0, y + CARD_HEIGHT + 2);
    }
}

void Dealer::StartAGame()
{
    // Get a new fresh deck
    this->_deck = Deck();
    // Remove every card from the players
    for (Player& player : this->_players)
    {
		player.ThrowCardsAway();
    }
    // Set current status of the game
	_status = Status::START;
    // Distribute card to each players
    this->distributeCards();

    // Every player check what pattern they have
    for (Player &player: this->_players)
    {
        player.SetHandStatus(HandStatus::SHOWING);
		player.SortHand();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
		player.CheckPattern();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

	// Determine the winner
	std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
        if (player1.GetPattern() == player2.GetPattern())
        {
            return player1.GetOrder() < player2.GetOrder();
        }

		return player1.GetPattern() > player2.GetPattern();
    });

	_status = Status::DISPLAY_RESULTS;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	_players.front().IncrementScore();

	this->_status = Status::WAITING;
}

void Dealer::distributeCards()
{
    // Shuffle the deck
	this->_deck.Shuffle();

    // While the deck is not empty, distribute a number of cards defined to each player
    for (int i = 0; i < START_CARD_PER_PLAYERS; i++)
    {
        for (Player& player : this->_players)
        {
            player.AddCard(this->_deck.PickACard());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (this->_deck.IsEmpty())
            {
                return;
            }
        }
    }
}

