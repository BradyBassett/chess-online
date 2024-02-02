#include "Move.h"

Move::Move(Position from, Position to, std::string promotion)
	: from(from), to(to), promotion(promotion) {
}

Position Move::getFrom() {
	return from;
}

Position Move::getTo() {
	return to;
}

std::string Move::getPromotion() {
	return promotion;
}