#ifndef ADVENTOFCODE2020_DAY07
#define ADVENTOFCODE2020_DAY07

#include "../includes/aoc.h"

class Day07 {
private:
	std::string inputString;
public:
	Day07()
	{
		inputString = util::readFile("..\\inputs\\input_2020_7.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY07
