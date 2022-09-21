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
	this->_totalBet = 0;
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
        const std::string name = player.GetName() + " (" + std::to_string(player.GetMoney()) + "$)";

        if (player.GetMoneyDiff() != 0)
        {
            _screen.Draw(Text{ (player.GetMoneyDiff() > 0 ? "+" : "-") + std::to_string(abs(player.GetMoneyDiff())),
                x + static_cast<int>((player.GetName() + " (" + std::to_string(player.GetMoney())).size()) - static_cast<int>((std::to_string(abs(player.GetMoneyDiff()))).size() + 1),
            	y + TEXT_Y_OFFSET - 1});
        }
        _screen.Draw(Text{name, x, y + TEXT_Y_OFFSET});
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

			x += CARD_WIDTH + 4;
    	}

    	if (player.GetPattern().GetPatternType() != PatternType::END) {
            _screen.Draw(Text{ static_cast<std::string>(player.GetPattern()), x + 3, y + TEXT_Y_OFFSET });
			x += NAME_WIDTH * 2;
    	}

        if (_status == Status::DISPLAY_RESULTS || _status == Status::WAITING)
        {
            // Display results, the place of the player
            _screen.Draw(Text{std::to_string(i + 1) + ((i + 1) == 1 ? "st" : "th") + " place", x, y + TEXT_Y_OFFSET });
        }

        y += CARD_HEIGHT + 1;
    }


    if (_status == Status::WAITING)
    {
		_screen.Draw(Text{ "Press Enter to continue or any other key to stop", _screen.GetWidth() / 2, y + 2, false, true });
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
        if (player.GetMoney() > 0)
        {
            for (int i = 0; i < 3; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
				player.DecreaseMoneyDiff(5);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
	        this->_totalBet += player.GetBet();
            player.ResetMoneyDiff();
        	player.SetHandStatus(HandStatus::SHOWING);
        	player.SortHand();
        	std::this_thread::sleep_for(std::chrono::milliseconds(500));
        	player.CheckPattern();
        	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

	// Determine the winner
	std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
		return player1.GetPattern() > player2.GetPattern();
    });

	_status = Status::DISPLAY_RESULTS;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int i = 0; i < 10; i++)
    {
		_players.front().IncreaseMoneyDiff(_totalBet / 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    _players.front().AddMoney(_totalBet);
    _players.front().ResetMoneyDiff();
    _totalBet = 0;
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
            if (player.GetMoney() > 0)
            {
	            player.AddCard(this->_deck.PickACard());
            	if (this->_deck.IsEmpty())
            	{
            		return;
            	}
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

