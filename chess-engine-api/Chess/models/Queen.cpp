#include "Queen.h"

Queen::Queen(Color pieceColor, Position currentPosition)
	: Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition), StraightPiece(pieceColor, currentPosition)
{
	pieceType = PieceType::Queen;
}

bool Queen::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(board, targetPosition, errorMessage))
	{
		return false;
	}

	if (!DiagonalPiece::isValidMove(board, targetPosition, errorMessage) && !StraightPiece::isValidMove(board, targetPosition, errorMessage))
	{
		errorMessage = "Invalid move - Queen can only move diagonally or straight";
		return false;
	}

	return true;
}

Bitboard Queen::getValidMoves(Board &board) const
{
	Bitboard validMoves = 0x0;

	// get valid moves for diagonal and straight moves
	validMoves |= DiagonalPiece::getValidMoves(board);
	validMoves |= StraightPiece::getValidMoves(board);

	return validMoves;
}