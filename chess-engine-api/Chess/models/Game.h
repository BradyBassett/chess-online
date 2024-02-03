#ifndef GAME_H
#define GAME_H

#include "../enums/Color.h"
#include "../structs/Position.h"
#include "../structs/Move.h"
#include "Board.h"
#include <string>
#include "Piece.h"
#include <optional>

class Game {
private:
	Color turn;
	Board board;

	char pieceToAscii(std::shared_ptr<Piece> piece);

	PieceType charToPieceType(char piece);

	Move composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece);

public:
	Game(std::string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); //w KQkq - 0 1

	Color getTurn();

	void changeTurn();

	std::string ascii();

	Move makeMove(Position from, Position to, char promotion = '\0');

	Position convertStringToPosition(std::string position);
};

#endif