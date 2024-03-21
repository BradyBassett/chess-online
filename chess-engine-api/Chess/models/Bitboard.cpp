#include "Board.h"

int Bitboard::getSquareNumber(Position position)
{
	return 8 * position.row + position.col;
}

Bitboard::Bitboard(uint64_t value) : value(value)
{
}

Bitboard::Bitboard(Position position)
{
	setBit(position);
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

bool Bitboard::operator==(const Bitboard &other) const
{
	return value == other.value;
}

bool Bitboard::operator!=(const Bitboard &other) const
{
	return value != other.value;
}

bool Bitboard::operator!=(uint64_t other) const
{
	return value != other;
}

uint64_t Bitboard::getValue()
{
	return value;
}

bool Bitboard::getBit(int index)
{
	return (value & (1ULL << index)) != 0;
}

bool Bitboard::getBit(Position position)
{
	return getBit(getSquareNumber(position));
}

void Bitboard::setValue(uint64_t bitboard)
{
	value = bitboard;
}

void Bitboard::setBit(Position position)
{
	value |= getBit(position);
}

void Bitboard::setBit(int row, int col)
{
	value |= getBit({row, col});
}

void Bitboard::clearBit(Position position)
{
	value ^= getBit(position);
}

void Bitboard::clearBit(int row, int col)
{
	value ^= getBit({row, col});
}