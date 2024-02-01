#include "Game.h"

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
	std::string result = "+------------------------+\n";

	for (uint8_t i = 8; i >= 1; i--) {
		result += std::to_string(i) + " | ";
		for (uint8_t j = 0; j < 8; j++) {
			result += pieceToAscii(board.getSquare(i, j).getPiece()) + " ";
		}
	}

	result += "+------------------------+\n";
	result += "  a  b  c  d  e  f  g  h\n";

	return result;
}

char Game::pieceToAscii(std::shared_ptr<Piece> piece) {
	switch (piece->getPieceType()) {
		case PieceType::Pawn:
			return (piece->getPieceColor() == Color::White) ? 'P' : 'p';
		case PieceType::Knight:
			return (piece->getPieceColor() == Color::White) ? 'N' : 'n';
		case PieceType::Bishop:
			return (piece->getPieceColor() == Color::White) ? 'B' : 'b';
		case PieceType::Rook:
			return (piece->getPieceColor() == Color::White) ? 'R' : 'r';
		case PieceType::Queen:
			return (piece->getPieceColor() == Color::White) ? 'Q' : 'q';
		case PieceType::King:
			return (piece->getPieceColor() == Color::White) ? 'K' : 'k';
		default:
			return ' ';
	}
}

Move Game::makeMove(std::string from, std::string to) {
	return Move(from, to);
}
