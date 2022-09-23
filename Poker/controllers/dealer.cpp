#include "Dealer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

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
	this->_status = Status::WAITING;
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
			x += NAME_WIDTH * 3;
    	}

        if (_status == Status::DISPLAY_RESULTS || _status == Status::WAITING)
        {
            // Display results, the place of the player
            bool isBest = false;
			for (Player bestPlayer: BestPlayers)
			{
                if (bestPlayer.GetName() == player.GetName())
                    isBest = true;
			}

            if (isBest)
            {
	            _screen.Draw(Text{static_cast<int>(BestPlayers.size()) > 1 ? "Draw" : "Winner", x, y + TEXT_Y_OFFSET});
            }
        }

        y += CARD_HEIGHT + 1;
    }


    if (_status == Status::WAITING)
    {
		_screen.Draw(Text{ "[Continue]", _screen.GetWidth() / 2, y + 2, true });
    }

    if (_status == Status::CHOOSING_BET)
    {
        // Display all bets choices
		
        int i = 0;
        std::string str = "Choose how many money you want to bet for him: ";
        
        for (int bet: Bets)
        {
			std::string betString = std::to_string(bet) + "$";
            if (i == SelectedChoice)
            {
				betString = "[" + betString + "]";
            }
            str += betString + "   ";

            i++;
        }

        _screen.Draw(Text{ str, _screen.GetWidth() / 2, y + 2, true });
    }

    if (CanEnterKey)
    {
	    _screen.Draw(Text{ "Enter: submit | Arrows <>: select choice | Esc: quit", _screen.GetWidth() / 2, _screen.GetHeight() - 2, true });
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
        if (player.GetMoney() == 0)
            continue;
        player.SetHandStatus(HandStatus::SHOWING);
        player.SortHand();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        player.CheckPattern();
        // Choose how many money to bet
        Bets = { player.GetMoney() / 10, player.GetMoney() / 4, player.GetMoney() / 2 };
        if (Bets[0] < 10)
        {
            if (player.GetMoney() < 10)
            {
                Bets = {player.GetMoney()};
            } else
            {
                Bets[0] = 10;
            }
		}
        if (Bets[1] < 25)
        {
            if (player.GetMoney() < 25)
            {
				Bets = { 10, player.GetMoney() };
			}
			else
			{
				Bets[1] = 25;
            }
        }
        if (Bets[2] < 50)
        {
            if (player.GetMoney() < 50)
            {
                Bets = { 10, 25, player.GetMoney() };
            }
            else
            {
                Bets[2] = 50;
            }
        }

        SelectedChoice = 0;
		_status = Status::CHOOSING_BET;
        // Let user choose the value of the bet
        WaitToEnterKey();
        _status = Status::START;
        CanEnterKey = false;
        for (int i = 0; i < 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
			player.DecreaseMoneyDiff(Bets[SelectedChoice] / 3);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        this->_totalBet += Bets[SelectedChoice];
        player.SubtractMoney(Bets[SelectedChoice]);
        player.ResetMoneyDiff();
    }

	// Determine the winner
	std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
		return player1.GetPattern() > player2.GetPattern();
    });

    auto bestPattern = Pattern(PatternType::HIGH_CARD, CardValue::TWO);
    BestPlayers = {};
    for (Player player: _players)
    {
        if (player.GetMoney() == 0)
            continue;
        if (player.GetPattern() > bestPattern)
        {
            BestPlayers = { player };
			bestPattern = player.GetPattern();
        } else if (player.GetPattern() == bestPattern)
        {
            BestPlayers.emplace_back(player);
        }
    }

    // Display who wins and the animation of the money going up
	_status = Status::DISPLAY_RESULTS;
    int betToGain = _totalBet / static_cast<int>(BestPlayers.size());
    for (Player &player: _players)
    {
        if (player.GetMoney() == 0)
            continue;
        bool isBest = false;
        for (const Player bestPlayer : BestPlayers)
        {
            if (bestPlayer.GetName() == player.GetName())
                isBest = true;
        }

        if (isBest)
        {
	        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        	for (int i = 0; i < 5; i++)
        	{
        		player.IncreaseMoneyDiff(betToGain / 5);
        		std::this_thread::sleep_for(std::chrono::milliseconds(200));
        	}
        	player.AddMoney(betToGain);
        	player.ResetMoneyDiff();
        }
    }
    
    _totalBet = 0;
}

void Dealer::WaitToEnterKey()
{
    CanEnterKey = true;
    switch (int key = _getch())
    {
    case KEY_DOWN:

        break;
    case KEY_UP:

        break;
    case KEY_RIGHT:
		if (_status == Status::CHOOSING_BET)
		{
            SelectedChoice++;
			if (SelectedChoice == static_cast<int>(Bets.size()))
			{
				SelectedChoice = 0;
			}
		}
        break;
    case KEY_LEFT:
		if (_status == Status::CHOOSING_BET)
		{
            SelectedChoice--;
			if (SelectedChoice < 0)
			{
				SelectedChoice = static_cast<int>(Bets.size()) - 1;
			}
		}
        break;
    case KEY_ENTER:
        if (_status == Status::WAITING)
        {
            CanEnterKey = false;
	        StartAGame();
	        SetStatus(Status::WAITING);
	        WaitToEnterKey();
        }
        return;
    case KEY_ESC:
        exit(0);
    }

    WaitToEnterKey();
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

