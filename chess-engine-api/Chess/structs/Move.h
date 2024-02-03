#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "../enums/MoveFlag.h"
#include <string>
#include <bitset>
#include <optional>

struct Move {
	std::bitset<7> flags; // NonCapture, PawnPush, EnPassant, StandardCapture, Promotion, KingsideCastling, QueensideCastling

	void setFlag(MoveFlag flag) {
		flags.set(flag);
	}

	bool hasFlag(MoveFlag flag) {
		return flags.test(flag);
	}

	Color color;
	Position from;
	Position to;
	PieceType piece;
	std::optional<PieceType> capturedPiece;
	std::optional<PieceType> promotion;
};

#endif