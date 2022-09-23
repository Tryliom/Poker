#include "controllers/Dealer.h"

#include <windows.h>
#include <iostream>
#include <thread>

int constexpr WIDTH = 1400;
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
	MoveWindow(console, 0, 0, WIDTH, HEIGHT, TRUE);
}

void main()
{
	SetupConsole();
    Dealer dealer;
	// Start a new thread to refresh the console output
	std::thread t([&dealer]()
	{
		while (true)
		{
			dealer.OnTick();
		}
	});
	t.detach();

	dealer.StartAGame();
	dealer.SetStatus(Status::WAITING);
	dealer.WaitToEnterKey();
}
