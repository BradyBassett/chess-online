#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include "../structs/Position.h"
#include "../enums/PieceType.h"
#include "../enums/Color.h"

class Bitboard
{
private:
	uint64_t value = 0ULL;

	int getSquareNumber(Position position);

public:
	Bitboard(uint64_t value = 0x0ULL);

	Bitboard operator|(const Bitboard &other) const;

	Bitboard &operator|=(const Bitboard &other);

	Bitboard operator&(const Bitboard &other) const;

	Bitboard &operator&=(const Bitboard &other);

	Bitboard operator^(const Bitboard &other) const;

	Bitboard &operator^=(const Bitboard &other);

	Bitboard operator~() const;

	Bitboard operator<<(uint64_t shift) const;

	Bitboard &operator<<=(uint64_t shift);

	Bitboard operator>>(uint64_t shift) const;

	Bitboard &operator>>=(uint64_t shift);

	uint64_t getValue();

	void setValue(uint64_t value);

	void setBit(Position position);

	void clearBit(Position position);
};

#endif