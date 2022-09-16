#include <iostream>

#include "controllers/Dealer.h"
#include "models/utility/utils.h"

void main()
{
    Dealer dealer;

    do
    {
		Utils::ClearConsole();
        dealer.StartAGame();
		std::cout << "Press Enter to continue or any other key to quit" << std::endl;
        if (std::cin.peek() != '\n') {
            break;
        }
        std::cin.ignore();
    } while (true);
}
