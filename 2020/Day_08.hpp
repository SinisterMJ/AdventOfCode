#ifndef ADVENTOFCODE2020_DAY08
#define ADVENTOFCODE2020_DAY08

#include "../includes/aoc.h"

class Day08 {
private:
	std::string inputString;
public:
	Day08()
	{
		inputString = util::readFile("..\\inputs\\input_2020_8.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY08
