#include "Bishop.h"

Bishop::Bishop(Color pieceColor, std::shared_ptr<Square> currentSquare) : Piece(pieceColor, currentSquare), DiagonalPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Bishop;
}
