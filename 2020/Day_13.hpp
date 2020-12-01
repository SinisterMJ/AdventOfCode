#ifndef ADVENTOFCODE2020_DAY13
#define ADVENTOFCODE2020_DAY13

#include "../includes/aoc.h"

class Day13 {
private:
	std::string input;
public:
	Day13()
	{
		input = util::readFile("..\\inputs\\input_2020_13.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY13
