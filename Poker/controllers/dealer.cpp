#include "Dealer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

Dealer::Dealer()
{
	this->_deck = Deck();
    for (int i = 0; i < NB_PLAYER; i++)
    {
		this->_players.emplace_back(Player("Player " + std::to_string(i), i));
    }
	this->_status = Status::IN_GAME;
}

void Dealer::OnTick()
{
    _display.Clear();
	this->Update();
    _display.Render();
}

void Dealer::Update()
{
    for (int i = 0; i < NB_PLAYER; i++)
    {
	    Player& player = this->_players[i];
    	std::string display = player.GetName() + " (" + std::to_string(player.GetScore()) + "p)" + ": ";
    	std::string cards;

    	for (Card card : player.GetHand())
    	{
    		if (!cards.empty())
    		{
    			cards += ", ";
    		}

    		cards += player.GetHandStatus() == HandStatus::HIDDEN ? "?" : static_cast<std::string>(card);
    	}

    	display += cards;

    	if (player.GetPattern().GetPatternType() != PatternType::END) {
            display += " -> " + static_cast<std::string>(player.GetPattern());

    		if (i == 0)
    		{
    			if (_players[i + 1].GetPattern() == _players[i].GetPattern())
    			{
    				display += " DRAW";
    			}
    			else
    			{
    				display += " WINNER";
    			}
    		}
    		else
    		{
    			for (int j = i - 1; j >= 0; j--)
    			{
    				if (_players[j].GetPattern() != _players[i].GetPattern()) {
    					break;
    				}

    				if (j == 0)
    				{
    					display += " DRAW";
    				}
    			}
    		}
    	}

        _display.Draw(display, 0, i);
    }


    if (_status == Status::WAITING)
    {
		_display.Draw("Press Enter to continue or any other key to stop", 0, NB_PLAYER + 2);
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
	_status = Status::IN_GAME;
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

	_players.front().IncrementScore();

    // Display win count for everyone
    std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
        return player1.GetScore() > player2.GetScore();
    });

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

