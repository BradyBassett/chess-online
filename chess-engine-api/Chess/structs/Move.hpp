#ifndef MOVE_HPP
#define MOVE_HPP

#include "Position.hpp"
#include "../enums/PieceType.hpp"
#include "../enums/Color.hpp"
#include "../enums/MoveFlag.hpp"
#include <string>
#include <bitset>
#include <optional>

struct Move
{
	std::bitset<7> flags; // NonCapture, PawnPush, EnPassant, StandardCapture, Promotion, KingsideCastling, QueensideCastling

	void setFlag(MoveFlag flag)
	{
		flags.set(flag);
	}

	bool hasFlag(MoveFlag flag)
	{
		return flags.test(flag);
	}

	Color color;
	Position from;
	Position to;
	PieceType piece;
	std::optional<PieceType> capturedPiece;
	std::optional<PieceType> promotion;
	uint8_t halfMoveClock;
	uint8_t fullMoveNumber;
};

#endif // MOVE_HPP