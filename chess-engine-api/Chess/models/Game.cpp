#include "Game.h"
#include "../enums/PieceType.h"
#include <stdexcept>

Game::Game(std::string fenPosition) : board(fenPosition) {
	turn = Color::White;
}

Color Game::getTurn() {
	return turn;
}

void Game::changeTurn() {
	turn = (turn == Color::White) ? Color::Black : Color::White;
}

std::string Game::ascii() {
	std::string result;

	for (int i = 0; i < 8; i++) {
		result += "--+---+---+---+---+---+---+---+---+\n";
		result += std::to_string(8 - i) + " | ";
		for (int j = 0; j < 8; j++) {
			Square& square = board.getSquare(i, j);
			std::shared_ptr<Piece> piece = square.getPiece();
			result += pieceToAscii(piece);
			result += " | ";
		}
		result += "\n";
	}

	return result += "--+---+---+---+---+---+---+---+---+\n  | a | b | c | d | e | f | g | h |\n";
}

char Game::pieceToAscii(std::shared_ptr<Piece> piece) {
	if (!piece) {
		return ' ';
	}

	Color pieceColor = piece->getPieceColor();
	
	switch (piece->getPieceType()) {
		case PieceType::Pawn:
			return (pieceColor == Color::White) ? 'P' : 'p';
		case PieceType::Knight:
			return (pieceColor == Color::White) ? 'N' : 'n';
		case PieceType::Bishop:
			return (pieceColor == Color::White) ? 'B' : 'b';
		case PieceType::Rook:
			return (pieceColor == Color::White) ? 'R' : 'r';
		case PieceType::Queen:
			return (pieceColor == Color::White) ? 'Q' : 'q';
		case PieceType::King:
			return (pieceColor == Color::White) ? 'K' : 'k';
		default:
			return ' ';
	}
}

PieceType Game::charToPieceType(char piece) {
	switch (piece) {
		case 'p':
			return PieceType::Pawn;
		case 'n':
			return PieceType::Knight;
		case 'b':
			return PieceType::Bishop;
		case 'r':
			return PieceType::Rook;
		case 'q':
			return PieceType::Queen;
		case 'k':
			return PieceType::King;
		default:
			throw std::invalid_argument("Invalid piece type");
	}
}

Move Game::composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece) {
	Move move;
	move.color = turn;
	move.from = from;
	move.to = to;
	move.piece = board.getSquare(from.row, from.col).getPiece()->getPieceType();

	if (promotion != '\0' && move.piece == PieceType::Pawn) {
		move.setFlag(MoveFlag::Promotion);
		move.promotion = charToPieceType(promotion);
	}

	if (capturedPiece.value() && capturedPiece.value()->getPieceColor() != turn) {
		move.setFlag(MoveFlag::StandardCapture); // FIXME - This is not necessarily a standard capture add a check for en passant
		move.capturedPiece = capturedPiece.value()->getPieceType();
	}

	return move;
}


Move Game::makeMove(Position from, Position to, char promotion) {
	if (from.row == to.row && from.col == to.col) {
		throw std::invalid_argument("Invalid move - Piece must move to a different square");
	}

	Move move;
	Square& fromSquare = board.getSquare(from.row, from.col);
	Square& toSquare = board.getSquare(to.row, to.col);
	
	if (!fromSquare.getPiece()) {
		throw std::invalid_argument("No piece at from position");
	}

	Piece& fromPiece = *fromSquare.getPiece();

	// check if move is valid
	if (!fromPiece.isValidMove(board, to)) {
		throw std::invalid_argument("Invalid move");
	}

	// compose the move struct
	move = composeMoveStruct(from, to, promotion, toSquare.getPiece());

	// move the piece
	board.movePiece(fromSquare, toSquare);
	
	return move;
}

Position Game::convertStringToPosition(std::string position) {
	return Position{8 - (position[1] - '0'), position[0] - 'a'};
}