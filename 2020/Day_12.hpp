#ifndef ADVENTOFCODE2020_DAY12
#define ADVENTOFCODE2020_DAY12

#include "../includes/aoc.h"

class Day12 {
private:
	std::vector<std::string> input;
public:
	Day12()
	{
		input = util::readFileLines("..\\inputs\\input_2020_12.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY12
