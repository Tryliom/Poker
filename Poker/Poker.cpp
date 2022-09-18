#include "controllers/Dealer.h"

#include <windows.h>
#include <iostream>
#include <thread>

int constexpr FPS = 60;

void HideConsoleCursor()
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(output, &cursorInfo);
	// set the cursor visibility
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(output, &cursorInfo);
}

void main()
{
	HideConsoleCursor();
	// Set console to UTF-8 in order to display emojis
    SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleA("Poker");
    Dealer dealer;
	std::thread t([&dealer]()
	{
		while (true)
		{
			dealer.OnTick();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
		}
	});
	t.detach();

    do
    {
        dealer.StartAGame();
		dealer.SetStatus(Status::WAITING);
		// Wait for the user to press enter or any other key to stop
        if (std::cin.peek() != '\n') {
            break;
        }
        std::cin.ignore();
    } while (true);
}
