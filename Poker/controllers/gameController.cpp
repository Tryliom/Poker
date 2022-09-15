#include "gameController.h"

#include <iostream>

GameController::GameController()
{
	this->_deck = Deck();
    for (int i = 0; i < NB_PLAYER; i++)
    {
        this->_players.emplace_back(Player());
    }
}	


void GameController::Start()
{
    // Distribute card to each players
    this->distributeCards();

    //TODO: Check who has the best suit value

}

void GameController::distributeCards()
{
    // While the deck is not empty, distribute a number of cards defined to each player
    for (Player player : this->_players)
    {
        for (int i = 0; i < START_CARD_PER_PLAYERS; i++)
        {
            player.AddCard(this->_deck.PickRandomCard());

            if (this->_deck.IsEmpty())
            {
                std::cout << "The deck is empty, we can't distribute more cards" << std::endl;
                return;
            }
        }
    }
}

void GameController::Restart()
{
	this->_deck = Deck();
}

