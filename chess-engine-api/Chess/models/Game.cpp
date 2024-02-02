#include "Game.h"
#include "../enums/PieceType.h"

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
		result += "+---+---+---+---+---+---+---+---+---+\n";
		result += std::to_string(8 - i) + " | ";
		for (int j = 0; j < 8; j++) {
			Square square = board.getSquare(i, j);
			std::shared_ptr<Piece> piece = square.getPiece();
			result += pieceToAscii(piece);
			result += " | ";
		}
		result += "\n";
	}

	return result += "+---+---+---+---+---+---+---+---+---+\n  | a | b | c | d | e | f | g | h |\n";
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

Move Game::makeMove(Position from, Position to, std::string promotion) {
	return Move(from, to, promotion);
}

Position Game::convertPosition(std::string position) {
	return Position{position[0] - 'a', 8 - (position[1] - '0')};
}