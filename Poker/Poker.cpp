#include "controllers/Dealer.h"

#include <windows.h>
#include <iostream>
#include <thread>

int constexpr FPS = 60;
int constexpr WIDTH = 1200;
int constexpr HEIGHT = 1000;

void SetupConsole()
{
	// Set console to UTF-8 in order to display emojis
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleA("Poker");
	// Set console size
	const HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, WIDTH, HEIGHT, TRUE);
}

void main()
{
	SetupConsole();
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
