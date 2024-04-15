#include "Board.hpp"

int Bitboard::getSquareNumber(Position position)
{
    int squareNumber = (position.row * 8) + position.col;
    return squareNumber;
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
	Bitboard bitboard = Bitboard(value | other.value);
	return bitboard;
}

Bitboard &Bitboard::operator|=(const Bitboard &other)
{
	value |= other.value;
	return *this;
}

Bitboard Bitboard::operator&(const Bitboard &other) const
{
	Bitboard bitboard = Bitboard(value & other.value);
	return bitboard;
}

Bitboard &Bitboard::operator&=(const Bitboard &other)
{
	value &= other.value;
	return *this;
}

Bitboard Bitboard::operator^(const Bitboard &other) const
{
	Bitboard bitboard = Bitboard(value ^ other.value);
	return bitboard;
}

Bitboard &Bitboard::operator^=(const Bitboard &other)
{
	value ^= other.value;
	return *this;
}

Bitboard Bitboard::operator~() const
{
	Bitboard bitboard = Bitboard(~value);
	return bitboard;
}

Bitboard Bitboard::operator<<(uint64_t shift) const
{
	Bitboard bitboard = Bitboard(value << shift);
	return bitboard;
}

Bitboard &Bitboard::operator<<=(uint64_t shift)
{
	value <<= shift;
	return *this;
}

Bitboard Bitboard::operator>>(uint64_t shift) const
{
	Bitboard bitboard = Bitboard(value >> shift);
	return bitboard;
}

Bitboard &Bitboard::operator>>=(uint64_t shift)
{
	value >>= shift;
	return *this;
}

bool Bitboard::operator==(const Bitboard &other) const
{
	bool isEqual = value == other.value;
	return isEqual;
}

bool Bitboard::operator!=(const Bitboard &other) const
{
	bool notEqual = value != other.value;
	return notEqual;
}

bool Bitboard::operator!=(uint64_t other) const
{
	bool notEqual = value != other;
	return notEqual;
}

uint64_t Bitboard::getValue()
{
	return value;
}

bool Bitboard::getBit(int squareNumber)
{
	uint64_t bit = (value & (1ULL << squareNumber));
	return bit != 0;
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
	uint64_t bit = 1ULL << getSquareNumber(position);
	value |= bit;
}

void Bitboard::setBit(int row, int col)
{
	uint64_t bit = 1ULL << getSquareNumber({row, col});
	value |= bit;
}

void Bitboard::clearBit(Position position)
{
	value ^= getBit(position);
}

void Bitboard::clearBit(int row, int col)
{
	value ^= getBit({row, col});
}