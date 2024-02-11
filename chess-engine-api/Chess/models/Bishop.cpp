#include "Bishop.h"

Bishop::Bishop(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition)
{
	pieceType = PieceType::Bishop;
}
