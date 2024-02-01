#include "Move.h"

Move::Move(std::string from, std::string to, char promotion)
	: from(std::move(from)), to(std::move(to)), promotion(promotion) {
}

std::string Move::getFrom() {
	return from;
}

std::string Move::getTo() {
	return to;
}

char Move::getPromotion() {
	return promotion;
}

std::string Move::toString() {
	return from + to + promotion;
}