#ifndef ROOK_HPP
#define ROOK_HPP

#include "OrthagonalPiece.hpp"
#include "../enums/Side.hpp"

class Rook : public OrthagonalPiece
{
private:
	Side side;

public:
	Rook(Color pieceColor, Position currentPosition, Side side = Side::None);

	Side getSide() const;
};

#endif // ROOK_HPP