#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "models/Game.h"

int main();

std::vector<std::string> splitFenString(const std::string &fenString)
{
	std::vector<std::string> parts;
	std::istringstream iss(fenString);
	std::string part;
	while (std::getline(iss, part, ' '))
	{
		parts.push_back(part);
	}

	return parts;
}

int main()
{
	std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::cout << "Enter Fen String (or press enter for default): ";
	std::string input;
	std::getline(std::cin, input);
	if (!input.empty())
	{
		fenString = input;
	}

	// split the fen string into its parts
	std::vector<std::string> fenParts = splitFenString(fenString);

	Game game = Game(fenParts);

	while (true)
	{
		std::cout << game.ascii() << std::endl;

		std::string line, from, to, promotion;

		std::cout << (game.getActiveColor() == Color::White ? "White" : "Black") << " - Enter move: ";
		std::getline(std::cin, line);

		std::istringstream iss(line);
		iss >> from >> to >> promotion;

		if (from == "quit")
		{
			break;
		}

		Position fromPosition = game.convertStringToPosition(from);
		Position toPosition = game.convertStringToPosition(to);

		try
		{
			std::system("clear");
			game.attemptMove(fromPosition, toPosition, promotion.c_str()[0]);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << "\n\n";
		}
	}

	return 0;
}

// find . -name "*.cpp" | xargs g++ -g -o main