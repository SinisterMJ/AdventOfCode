#ifndef ADVENTOFCODE2020_DAY11
#define ADVENTOFCODE2020_DAY11

#include "../includes/aoc.h"

class Day11 {
private:
	std::string inputString;
public:
	Day11()
	{
		inputString = util::readFile("..\\inputs\\input_2020_11.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY11
