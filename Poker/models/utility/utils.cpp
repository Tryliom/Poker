#include <random>

namespace Utils
{
	int GetRandomInt(const int min, const int max) {
		std::random_device osSeed;
		const uint_least32_t seed = osSeed();

		std::mt19937 generator(seed);
		std::uniform_int_distribution<uint_least32_t> distribute(min, max);

		return distribute(generator);
	}

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
