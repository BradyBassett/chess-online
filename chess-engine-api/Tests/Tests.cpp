#include "Tests.hpp"
#include <random>
#include <iostream>

uint64_t Tests::generateRandomUint64Value() {
    std::random_device rd;
    std::mt19937_64 generator(rd());

    uint64_t value = generator();

	return value;
}
