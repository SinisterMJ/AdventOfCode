#ifndef ADVENTOFCODE2020_DAY25
#define ADVENTOFCODE2020_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
	std::string inputString;
public:
	Day25()
	{
		inputString = util::readFile("..\\inputs\\input_2020_25.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY25
