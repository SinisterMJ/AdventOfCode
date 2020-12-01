#ifndef ADVENTOFCODE2020_DAY16
#define ADVENTOFCODE2020_DAY16

#include <map>

#include "../includes/aoc.h"

class Day16 {
private:
	std::string inputString;
public:
	Day16()
	{
		inputString = util::readFile("..\\inputs\\input_2020_16.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY16
