#include "Queen.h"

Queen::Queen(Color pieceColor, Position currentPosition)
	: Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition), StraightPiece(pieceColor, currentPosition)
{
	pieceType = PieceType::Queen;
}

bool Queen::isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(game, targetPosition, errorMessage))
	{
		return false;
	}

	if (!DiagonalPiece::isValidMove(game, targetPosition, errorMessage) && !StraightPiece::isValidMove(game, targetPosition, errorMessage))
	{
		errorMessage = "Invalid move - Queen can only move diagonally or straight";
		return false;
	}

	return true;
}

Bitboard Queen::getValidMoves(Game &game) const
{
	Bitboard validMoves = 0x0;

	// get valid moves for diagonal and straight moves
	validMoves |= DiagonalPiece::getValidMoves(game);
	validMoves |= StraightPiece::getValidMoves(game);

	return validMoves;
}