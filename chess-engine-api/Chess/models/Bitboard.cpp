#include "Board.hpp"
#include <stdexcept>

int Bitboard::getSquareNumber(Position position)
{
    int squareNumber = (position.row * 8) + position.col;
    return squareNumber;
}

void Bitboard::checkPositionBounds(Position position)
{
	if (position.row < 0 || position.row > 7 || position.col < 0 || position.col > 7)
	{
		throw std::invalid_argument("Position out of bounds");
	}
}

Bitboard::Bitboard(uint64_t value) : value(value)
{
}

Bitboard::Bitboard(Position position)
{
	checkPositionBounds(position);

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
	if (shift >= 64) {
		return Bitboard(0);
	}

	Bitboard bitboard = Bitboard(value << shift);
	return bitboard;
}

Bitboard &Bitboard::operator<<=(uint64_t shift)
{
	if (shift >= 64) {
		value = 0;
		return *this;
	}

	value <<= shift;
	return *this;
}

Bitboard Bitboard::operator>>(uint64_t shift) const
{
	if (shift >= 64) {
		return Bitboard(0);
	}

	Bitboard bitboard = Bitboard(value >> shift);
	return bitboard;
}

Bitboard &Bitboard::operator>>=(uint64_t shift)
{
	if (shift >= 64) {
		value = 0;
		return *this;
	}

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

uint64_t Bitboard::getValue()
{
	return value;
}

bool Bitboard::getBit(int squareNumber)
{
	checkPositionBounds({squareNumber / 8, squareNumber % 8});

	uint64_t bit = (value & (1ULL << squareNumber));
	return bit != 0;
}

bool Bitboard::getBit(Position position)
{
	checkPositionBounds(position);

	return getBit(getSquareNumber(position));
}

void Bitboard::setValue(uint64_t bitboard)
{
	value = bitboard;
}

void Bitboard::setBit(Position position)
{
	checkPositionBounds(position);

	uint64_t bit = 1ULL << getSquareNumber(position);
	value |= bit;
}

void Bitboard::clearBit(Position position)
{
	checkPositionBounds(position);

	value &= ~(1ULL << getSquareNumber(position));
}
