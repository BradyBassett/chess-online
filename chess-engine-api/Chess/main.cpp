#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "models/Game.h"

int main();

int main() {
	Game game = Game();

	while (true)	{
		std::system("clear");
		std::cout << game.ascii() << std::endl;

		std::string line, from, to, promotion;

		std::cout << "Enter move: ";
		std::getline(std::cin, line);

		std::istringstream iss(line);
		iss >> from >> to >> promotion;

		if (from == "quit") {
			break;
		}

		Position fromPosition = game.convertPosition(from);
		Position toPosition = game.convertPosition(to);

		game.makeMove(fromPosition, toPosition, promotion);
	}
	

	return 0;
}

// find . -name "*.cpp" | xargs g++ -g -o main