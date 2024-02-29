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
	Color activeColor;
	Board board;
	std::vector<Move> moves;
	uint8_t halfMoveClock;
	uint8_t fullMoveNumber;
	Square *enPassantTargetSquare;
	bool whiteCanCastleKingside;
	bool whiteCanCastleQueenside;
	bool blackCanCastleKingside;
	bool blackCanCastleQueenside;

	std::vector<std::string> splitFenString(const std::string &fenString);

	void parsePiecePositions(const std::string &positions);

	void parseActiveColor(const std::string &color);

	void parseCastlingAvailability(const std::string &castling);

	void parseEnPassantTarget(const std::string &enPassant);

	void parseHalfmoveClock(const std::string &halfmove);

	void parseFullmoveNumber(const std::string &fullmove);

	char pieceToAscii(std::shared_ptr<Piece> piece);

	PieceType charToPieceType(char piece);

	Move composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece);

public:
	Game(std::vector<std::string> fenParts);

	Color getActiveColor();

	void switchActiveColor();

	Board &getBoard();

	std::string ascii();

	Move attemptMove(Position from, Position to, char promotion = '\0');

	void handlePawnPromotion(Piece &fromPiece, Square &fromSquare, Position to, Position from, char promotion);

	std::optional<std::shared_ptr<Piece>> getCapturedPiece(Square &toSquare, Position from, Position to, Piece &fromPiece);

	void updateCastlingAvailability(Piece &fromPiece);

	void updateEnPassantTargetSquare(Piece &fromPiece, Position from, Position to);

	Position convertStringToPosition(std::string position);

	std::vector<Move> getMoves();

	Move getLastMove();

	void addMove(Move move);

	void undoPreviousMove();

	uint8_t getHalfMoveClock();

	uint8_t getFullMoveNumber();

	void incrementHalfMoveClock();

	void resetHalfMoveClock();

	void incrementFullMoveNumber();
};

#endif