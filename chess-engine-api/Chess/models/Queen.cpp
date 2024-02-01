#include "Queen.h"

Queen::Queen(Color pieceColor, std::shared_ptr<Square> currentSquare) 
	: Piece(pieceColor, currentSquare), DiagonalPiece(pieceColor, currentSquare), StraightPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Queen;
}

bool Queen::isValidMove(Board& board, Square& targetSquare) const {
	if (!Piece::isValidMove(board, targetSquare)) {
		return false;
	}

	if (DiagonalPiece::isValidMove(board, targetSquare) || StraightPiece::isValidMove(board, targetSquare)) {
		return true;
	}

	return false;
}