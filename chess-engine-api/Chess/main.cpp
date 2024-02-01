#include <iostream>
#include "models/Game.h"

int main();

int main() {
	std::cout << "Hello, World!" << std::endl;

	Game game = Game();
	std::cout << game.ascii() << std::endl;

	return 0;
}

// find . -name "*.cpp" | xargs g++ -o main