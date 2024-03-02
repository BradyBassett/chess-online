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
	// TODO - Add a way to load a game from a PGN file and eventually save games to PGN
	// TODO - Implement Evaluation function
	// TODO - Implement Search function
	// TODO - Implement Transposition table
	// TODO - Implement Opening book
	// TODO - Implement Endgame tablebases
	// TODO - Add a way to play against the engine
	// TODO - Add tests for everything - DO THIS BEFORE STARTING THE ENGINE FOR THE LOVE OF GOD
	// TODO - Add a way to play the engine against itself
	// TODO - Add a way to play the engine against another engine
	// TODO - Add a way to play the engine against its older versions
	// TODO - Add Checkmate, Stalemate, and Draw detection
	// TODO - Add console arguments for undoing moves and specifying preferred color
	// TODO - Implement a way to communicate with the web app
	// TODO - Implement a way to communicate with UCI

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