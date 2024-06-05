#ifndef PERFTEST_HPP
#define PERFTEST_HPP

#include "../GameTest.hpp"

struct PerftTestParams
{
	std::string fen;
	int depth;
	std::vector<int> expectedNodes;
};

class PerftTest : public GameTest
{
private:

protected:
	PerftTestParams param;

public:
	PerftTest();
	static std::vector<std::pair<std::string, PerftTestParams>> testCases;
};

#endif // PERFTEST_HPP