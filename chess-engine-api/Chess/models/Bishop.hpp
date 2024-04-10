#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "DiagonalPiece.hpp"

class Bishop : public DiagonalPiece
{
public:
	Bishop(Color pieceColor, Position currentPosition);
};

#endif // BISHOP_HPP