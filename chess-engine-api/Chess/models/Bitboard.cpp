#include "Board.h"

int Bitboard::getSquareNumber(Position position)
{
	return 8 * position.row + position.col;
}

Bitboard::Bitboard(uint64_t value) : value(value)
{
}

Bitboard Bitboard::operator|(const Bitboard &other) const
{
	return Bitboard(value | other.value);
}

Bitboard &Bitboard::operator|=(const Bitboard &other)
{
	value |= other.value;
	return *this;
}

Bitboard Bitboard::operator&(const Bitboard &other) const
{
	return Bitboard(value & other.value);
}

Bitboard &Bitboard::operator&=(const Bitboard &other)
{
	value &= other.value;
	return *this;
}

Bitboard Bitboard::operator^(const Bitboard &other) const
{
	return Bitboard(value ^ other.value);
}

Bitboard &Bitboard::operator^=(const Bitboard &other)
{
	value ^= other.value;
	return *this;
}

Bitboard Bitboard::operator~() const
{
	return Bitboard(~value);
}

Bitboard Bitboard::operator<<(uint64_t shift) const
{
	return Bitboard(value << shift);
}

Bitboard &Bitboard::operator<<=(uint64_t shift)
{
	value <<= shift;
	return *this;
}

Bitboard Bitboard::operator>>(uint64_t shift) const
{
	return Bitboard(value >> shift);
}

Bitboard &Bitboard::operator>>=(uint64_t shift)
{
	value >>= shift;
	return *this;
}

uint64_t Bitboard::getValue()
{
	return value;
}

void Bitboard::setValue(uint64_t bitboard)
{
	value = bitboard;
}

void Bitboard::setBit(Position position)
{
	value |= 1ULL << getSquareNumber(position);
}

void Bitboard::clearBit(Position position)
{
	value ^= (1ULL << getSquareNumber(position));
}