#include "Tests.hpp"
#include <random>
#include <iostream>

uint64_t Tests::generateRandomUint64Value(uint64_t min, uint64_t max) {
    std::random_device rd;
    std::mt19937_64 generator(rd());

    std::uniform_int_distribution<uint64_t> distribution(min, max);
    uint64_t value = distribution(generator);

    return value;
}