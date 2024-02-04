#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "models/Game.h"

int main();

int main() {
	Game game = Game();

	while (true)	{
		std::cout << game.ascii() << std::endl;

		std::string line, from, to, promotion;

		std::cout << "Enter move: ";
		std::getline(std::cin, line);

		std::istringstream iss(line);
		iss >> from >> to >> promotion;

		if (from == "quit") {
			break;
		}

		Position fromPosition = game.convertStringToPosition(from);
		Position toPosition = game.convertStringToPosition(to);

		try
		{
			std::system("clear");
			game.makeMove(fromPosition, toPosition, promotion.c_str()[0]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "\n\n";
		}
	}
	

	return 0;
}

// find . -name "*.cpp" | xargs g++ -g -o main