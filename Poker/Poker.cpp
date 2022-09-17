#include "controllers/Dealer.h"
#include "models/utility/utils.h"

#include <windows.h>
#include <iostream>

void main()
{
	// Set console to UTF-8 in order to display emojis
    SetConsoleOutputCP(CP_UTF8);
    Dealer dealer;

    do
    {
		Utils::ClearConsole();
        dealer.StartAGame();
		std::cout << "Press Enter to continue or any other key to quit" << std::endl;
		// Wait for the user to press enter or any other key to stop
        if (std::cin.peek() != '\n') {
            break;
        }
        std::cin.ignore();
    } while (true);
}
