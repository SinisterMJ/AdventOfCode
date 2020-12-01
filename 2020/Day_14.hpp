#ifndef ADVENTOFCODE2020_DAY14
#define ADVENTOFCODE2020_DAY14

#include "../includes/aoc.h"


class Day14 {
private:
	std::vector<std::string> input;
public:
	Day14()
	{
		input = util::readFileLines("..\\inputs\\input_2020_14.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY14
