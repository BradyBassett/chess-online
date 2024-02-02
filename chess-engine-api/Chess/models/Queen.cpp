#include "Queen.h"

Queen::Queen(Color pieceColor, Position currentPosition) 
	: Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition), StraightPiece(pieceColor, currentPosition) {
	pieceType = PieceType::Queen;
}

bool Queen::isValidMove(Board& board, Position targetPosition) const {
	if (!Piece::isValidMove(board, targetPosition)) {
		return false;
	}

	if (DiagonalPiece::isValidMove(board, targetPosition) || StraightPiece::isValidMove(board, targetPosition)) {
		return true;
	}

	return false;
}