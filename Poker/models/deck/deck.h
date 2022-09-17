#pragma once
#include "card.h"

#include <vector>

class Deck
{
	private:
		std::vector<Card> _cards;

	public:
		Deck();
		/**
		 * \brief Shuffle the deck
		 */
		void Shuffle();
		/**
		 * @brief Pick a card from the top of the deck and delete it from the deck
		 * @return {Card} A unique card from the deck
		 */
		Card PickACard();
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

			for (auto &card : this->_cards)
			{
				result += "\n" + static_cast<std::string>(card);
			}

			return result;
		}

};

