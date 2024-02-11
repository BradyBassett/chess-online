#ifndef BISHOP_H
#define BISHOP_H

#include "DiagonalPiece.h"

class Bishop : public DiagonalPiece
{
public:
	Bishop(Color pieceColor, Position currentPosition);
};

#endif