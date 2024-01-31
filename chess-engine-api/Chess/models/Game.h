#ifndef GAME_H
#define GAME_H

#include "../enums/PieceColor.h"
#include "Board.h"
#include "Move.h"
#include <string>

class Game {
private:
	PieceColor turn;
	Board board;

public:
	Game(std::string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	PieceColor getTurn();

	void changeTurn();

	std::string ascii();

	Move makeMove(std::string from, std::string to);
};

#endif