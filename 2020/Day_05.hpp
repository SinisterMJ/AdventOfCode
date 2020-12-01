#ifndef ADVENTOFCODE2020_DAY05
#define ADVENTOFCODE2020_DAY05

#include "../includes/aoc.h"

class Day05 {
private:
	std::string inputString;
public:
	Day05()
	{
		inputString = util::readFile("..\\inputs\\input_2020_5.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
						
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY05
