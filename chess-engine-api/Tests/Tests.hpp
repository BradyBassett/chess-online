#ifndef TESTS_HPP
#define TESTS_HPP

#include <gtest/gtest.h>
#include <limits>

class Tests
{
private:

protected:

public:
	static uint64_t generateRandomUint64Value(uint64_t min = std::numeric_limits<uint64_t>::min(), uint64_t max = std::numeric_limits<uint64_t>::max());
};

#endif // TESTS_HPP