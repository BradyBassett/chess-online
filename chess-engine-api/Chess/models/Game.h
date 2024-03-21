#ifndef GAME_H
#define GAME_H

#include "../enums/Color.h"
#include "../enums/GameEndState.h"
#include "../structs/Position.h"
#include "../structs/Move.h"
#include "Piece.h"
#include "Board.h"
#include <string>
#include <optional>
#include <vector>
#include "King.h"

class Board;

class Game
{
private:
	Color activeColor;
	Board board;
	std::vector<Move> moves;
	uint8_t halfMoveClock;
	uint8_t fullMoveNumber;
	bool whiteInCheck = false;
	bool blackInCheck = false;

	std::vector<std::string> splitFenString(const std::string &fenString);

	void parsePiecePositions(const std::string &positions);

	void parseActiveColor(const std::string &color);

	void parseHalfmoveClock(const std::string &halfmove);

	void parseFullmoveNumber(const std::string &fullmove);

	char pieceToAscii(std::shared_ptr<Piece> piece);

	PieceType charToPieceType(char piece);

	Move composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece);

	Move prepareMove(Position from, Position to, char promotion);

	void executeMove(Move move);

	void postMoveChecks();

public:
	Game(std::vector<std::string> fenParts);

	Color getActiveColor();

	void switchActiveColor();

	Board &getBoard();

	std::string ascii();

	void attemptMove(Position from, Position to, char promotion = '\0');

	void handlePawnPromotion(Pawn &pawn, Position to, Position from, char promotion);

	std::optional<std::shared_ptr<Piece>> getCapturedPiece(Square &toSquare, Position from, Position to, Piece &fromPiece);

	std::vector<Move> getMoves();

	Move getLastMove();

	void addMove(Move move);

	void undoPreviousMove();

	uint8_t getHalfMoveClock();

	uint8_t getFullMoveNumber();

	void incrementHalfMoveClock();

	void resetHalfMoveClock();

	void incrementFullMoveNumber();

	bool getInCheck(Color color);

	void setInCheck(Color color, bool value);

	bool isInCheck(Color color, Position position);

	bool isCheckmate(Color color);

	bool isStalemate(Color color);

	bool isDraw();

	bool isFiftyMoveRule();

	bool isThreefoldRepetition();

	bool isInsufficientMaterial();

	bool isResignation();

	bool isTimeout();

	GameEndState isGameOver();

	bool isValidCastle(Position from, Position to, King &king, std::string &errorMessage);

	void validateGenericMove(Position from, Position to, Piece &fromPiece, Square &toSquare);

	void validatePawnMove(Position from, Position to, Piece &fromPiece, Square &toSquare);

	void validateKingMove(Position from, Position to, Piece &fromPiece);
};

#endif