#ifndef ADVENTOFCODE2020_DAY21
#define ADVENTOFCODE2020_DAY21

#include "../includes/aoc.h"

class Day21 {
private:
	std::string inputString;
	
public:
	Day21()
	{
		inputString = util::readFile("..\\inputs\\input_2020_21.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY21
