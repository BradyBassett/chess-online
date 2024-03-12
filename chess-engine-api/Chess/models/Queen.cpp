#include "Queen.h"

Queen::Queen(Color pieceColor, Position currentPosition)
	: Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition), OrthagonalPiece(pieceColor, currentPosition)
{
	pieceType = PieceType::Queen;
}

bool Queen::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(board, targetPosition, errorMessage))
	{
		return false;
	}

	if (!DiagonalPiece::isValidMove(board, targetPosition, errorMessage) && !OrthagonalPiece::isValidMove(board, targetPosition, errorMessage))
	{
		errorMessage = "Invalid move - Queen can only move diagonally or orthagonally";
		return false;
	}

	return true;
}

Bitboard Queen::getValidMoves(Board &board) const
{
	Bitboard validMoves = 0x0;

	// get valid moves for diagonal and orthagonal moves
	validMoves |= DiagonalPiece::getValidMoves(board);
	validMoves |= OrthagonalPiece::getValidMoves(board);

	return validMoves;
}