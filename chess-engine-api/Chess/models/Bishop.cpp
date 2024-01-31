#include "Bishop.h"

Bishop::Bishop(PieceColor pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare), DiagonalPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Bishop;
}
