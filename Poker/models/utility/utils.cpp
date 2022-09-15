#include <cstdlib>

namespace Utils
{
	void ClearConsole() {
		#if defined _WIN32
			// For windows
			system("cls");
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
			// For linux or Apple
			system("clear");
		#endif
	}
}
