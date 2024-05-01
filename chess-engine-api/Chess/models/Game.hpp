#ifndef GAME_HPP
#define GAME_HPP

#include "../enums/Color.hpp"
#include "../enums/GameEndState.hpp"
#include "../structs/Position.hpp"
#include "../structs/Move.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include <string>
#include <optional>
#include <vector>
#include <unordered_map>
#include "King.hpp"
#include "Pawn.hpp"

class Board;

class Game
{
private:
	Color activeColor;
	Board board;
	std::vector<Move> moves;
	// ? If performance becomes an issue, consider hashing the board state using Zobrist hashing
	std::unordered_map<std::string, int> gameStateHistory;
	int halfMoveClock;
	int fullMoveNumber;
	bool whiteInCheck = false;
	bool blackInCheck = false;

	std::vector<std::string> splitFenString(const std::string &fenString);

	void parseActiveColor(const std::string &color);

	void parseHalfmoveClock(const std::string &halfmove);

	void parseFullmoveNumber(const std::string &fullmove);

	char pieceToAscii(std::shared_ptr<Piece> piece);

	PieceType charToPieceType(char piece);

	Move composeMoveStruct(Position from, Position to, char promotion, Piece &fromPiece, std::optional<std::shared_ptr<Piece>> capturedPiece);

	Move prepareMove(Position from, Position to, char promotion);

	void executeMove(Move move, char promotion);

	void postMoveChecks();

	void undoPromotion(Move lastMove);

	void restoreMovedPiece(Move lastMove, std::shared_ptr<Piece> piece, Color color);

	void restoreCapturedPiece(Move lastMove, Color color);

	void undoCastle(Move lastMove, Color color);

	void undoDoublePawnPush(Move lastMove, std::shared_ptr<Piece> piece);

public:
	Game(std::string fenString);

	Color getActiveColor();

	void switchActiveColor();

	Board &getBoard();

	std::string ascii();

	void attemptMove(Position from, Position to, char promotion = '\0');

	void handlePawnPromotion(Piece &pawn, Position to, Position from, char promotion);

	std::optional<std::shared_ptr<Piece>> getCapturedPiece(Square &toSquare, Position from, Position to, Piece &fromPiece);

	std::vector<Move> getMoves();

	Move &getLastMove();

	void addMove(Move move);

	void undoPreviousMove();

	int getHalfMoveClock();

	int getFullMoveNumber();

	void incrementHalfMoveClock();

	void resetHalfMoveClock();

	void incrementFullMoveNumber();

	void setHalfMoveClock(int value);

	void setFullMoveNumber(int value);

	bool getInCheck(Color color);

	void setInCheck(Color color, bool value);

	bool isInCheck(Color color, Position position);

	bool isCheckmate(Color color);

	bool isStalemate(Color color);

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

	void validateMove(Position from, Position to, Piece &fromPiece, Square &toSquare);

	std::string getFen();

	std::vector<Move> generateLegalMoves();

	uint64_t Perft(int depth);
};

#endif // GAME_HPP