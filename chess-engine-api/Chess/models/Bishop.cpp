#include "Bishop.h"

Bishop::Bishop(Color pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare), DiagonalPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Bishop;
}
