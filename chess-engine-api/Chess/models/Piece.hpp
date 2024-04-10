#ifndef PIECE_HPP
#define PIECE_HPP

#include <memory>
#include "../enums/PieceType.hpp"
#include "../enums/Color.hpp"
#include "../structs/Position.hpp"
#include "Bitboard.hpp"

class Piece
{
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	Color pieceColor;
	PieceType pieceType;
	Position currentPosition;

public:
	Piece(Color pieceColor, Position currentPosition, PieceType pieceType = PieceType::Unknown);

	Piece(const Piece &piece) noexcept;

	bool getHasMoved() const;

	void setHasMoved(bool value = true);

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	Position getCurrentPosition() const;

	void setCurrentPosition(Position newPosition);

	virtual bool canPromote(Position targetPosition) const;

	Bitboard generateAttacks(const Position (&directions)[4]) const;

	virtual Bitboard getPotentialMoves() const;
};

#endif // PIECE_HPP