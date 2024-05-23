#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "models/Game.hpp"

int main();

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
	// TODO - Add Stalemate and Draw detection
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

	Game game = Game(fenString);

	bool isGameOver = false;
	while (!isGameOver)
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

		Position fromPosition = game.getBoard().convertStringToPosition(from);
		Position toPosition = game.getBoard().convertStringToPosition(to);

		try
		{
			std::system("clear");
			game.attemptMove(fromPosition, toPosition, promotion.c_str()[0]);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << "\n\n";
			continue;
		}

		switch (game.isGameOver())
		{
		case GameEndState::CHECKMATE:
			if (game.getActiveColor() == Color::White)
			{
				std::cout << "Checkmate - Black wins!" << std::endl;
			}
			else
			{
				std::cout << "Checkmate - White wins!" << std::endl;
			}

			isGameOver = true;
			break;
		case GameEndState::STALEMATE:
			std::cout << "Stalemate!" << std::endl;

			isGameOver = true;
			break;
		case GameEndState::RESIGNATION:
			std::cout << "Resignation!" << std::endl;

			isGameOver = true;
			break;
		case GameEndState::TIMEOUT:
			std::cout << "Timeout!" << std::endl;

			isGameOver = true;
			break;
		case GameEndState::THREEFOLD_REPETITION:
			std::cout << "Threefold Repetition!" << std::endl;

			isGameOver = true;
			break;
		case GameEndState::FIFTY_MOVE_RULE:
			std::cout << "Fifty Move Rule!" << std::endl;

			isGameOver = true;
			break;
		case GameEndState::INSUFFICIENT_MATERIAL:
			std::cout << "Insufficient Material!" << std::endl;

			isGameOver = true;
			break;
		}
	}

	std::cout << game.ascii() << std::endl;

	return 0;
}

// find . -name "*.cpp" | xargs g++ -g -o main