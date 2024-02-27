#ifndef GAME_H
#define GAME_H

#include "../enums/Color.h"
#include "../structs/Position.h"
#include "../structs/Move.h"
#include "Piece.h"
#include "Board.h"
#include <string>
#include <optional>
#include <vector>

class Board;

class Game
{
private:
	Color turn;
	Board board;
	std::vector<Move> moves;

	char pieceToAscii(std::shared_ptr<Piece> piece);

	PieceType charToPieceType(char piece);

	Move composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece);

public:
	Game(std::string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); // w KQkq - 0 1

	Color getTurn();

	void changeTurn();

	Board &getBoard();

	std::string ascii();

	Move makeMove(Position from, Position to, char promotion = '\0');

	Position convertStringToPosition(std::string position);

	std::vector<Move> getMoves();

	Move getLastMove();

	void addMove(Move move);

	void undoPreviousMove();
};

#endif