#ifndef ROOK_H
#define ROOK_H

#include "StraightPiece.h"

class Rook : public StraightPiece {
public:
	Rook(Color pieceColor, Square& currentSquare);
};

#endif