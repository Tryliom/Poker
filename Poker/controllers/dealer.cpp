#include "Dealer.h"

#include <algorithm>
#include <iostream>

Dealer::Dealer()
{
	this->_deck = Deck();
    for (int i = 0; i < NB_PLAYER; i++)
    {
		this->_players.emplace_back(Player("Player " + std::to_string(i)));
    }
}	

void Dealer::StartAGame()
{
    // Distribute card to each players
    this->distributeCards();

    // Every player check what pattern they have
    for (Player &player: this->_players)
    {
		player.CheckPattern();
    }

	// Determine the winner
	std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
		return player1.GetPattern() > player2.GetPattern();
    });

    // Display score of every one
	for (int i = 0; i < NB_PLAYER; i++)
	{
        Player& player = this->_players[i];
        std::string display = player.GetName() + ": ";
        std::string cards;

		for (Card card : player.GetHand())
		{
			if (!cards.empty())
			{
                cards += ", ";
			}

            cards += static_cast<std::string>(card);
		}

		display += cards + " -> " + static_cast<std::string>(player.GetPattern());

		if (i == 0)
		{
            if (_players[i+1].GetPattern() == _players[i].GetPattern())
            {
                display += " DRAW";
            } else
            {
                display += " WINNER";
                _players[i].IncrementScore();
            }
		} else
		{
			for (int j = i-1;j >= 0;j--)
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

		std::cout << display << std::endl;
	}

    // Get a new fresh deck
    this->_deck = Deck();
    // Remove every card from the players
    for (Player &player: this->_players)
    {
        player.ClearHand();
    }

    // Display win count for everyone
    std::sort(_players.begin(), _players.end(), [](const Player& player1, const Player& player2) {
        return player1.GetScore() > player2.GetScore();
    });

    std::cout << std::endl << std::endl << "Scores:" << std::endl;
    for (Player& player : this->_players)
    {
        std::cout << player.GetName() << ": " << player.GetScore() << " points" << std::endl;
    }
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

            if (this->_deck.IsEmpty())
            {
                std::cout << "The deck is empty, we can't distribute more cards" << std::endl;
                return;
            }
        }
    }
}

