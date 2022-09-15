#pragma once
#include <vector>

#include "card.h"

class Deck
{
	private:
		std::vector<Card> _cards;

	public:
		Deck();
		/**
		 * @brief Pick a random card from deck and delete it from the deck
		 * @return {Card} A unique card from the deck
		 */
		Card PickRandomCard();
        /**
         * \brief Check if the deck is empty
         * \return {bool} return true if the deck is empty, false otherwise
         */
        bool IsEmpty() const;
		/**
		 * \brief Return the content of the deck as a string
		 */
		explicit operator std::string() const
		{
			std::string result = "This deck contains " + std::to_string(this->_cards.size()) + " cards:";

			for (Card card : this->_cards)
			{
				result += "\n" + static_cast<std::string>(card);
			}

			return result;
		}

};

