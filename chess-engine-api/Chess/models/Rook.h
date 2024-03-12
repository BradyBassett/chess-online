#ifndef ROOK_H
#define ROOK_H

#include "OrthagonalPiece.h"

class Rook : public OrthagonalPiece
{
private:
	Side side;

public:
	Rook(Color pieceColor, Position currentPosition, Side side = Side::None);

	Side getSide() const;
};

#endif