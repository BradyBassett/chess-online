#ifndef ROOK_H
#define ROOK_H

#include "StraightPiece.h"

class Rook : public StraightPiece {
private:
	Side side;

public:
	Rook(Color pieceColor, Position currentPosition);

	Side getSide() const;
};

#endif