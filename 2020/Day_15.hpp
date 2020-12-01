#ifndef ADVENTOFCODE2020_DAY15
#define ADVENTOFCODE2020_DAY15

#include "../includes/aoc.h"

class Day15 {
private:
	std::string inputString;
public:
	Day15()
	{
		inputString = util::readFile("..\\inputs\\input_2020_15.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY15
