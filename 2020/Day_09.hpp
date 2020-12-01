#ifndef ADVENTOFCODE2020_DAY09
#define ADVENTOFCODE2020_DAY09

#include "../includes/aoc.h"

class Day09 {
private:
	std::string inputString;
public:
	Day09()
	{
		inputString = util::readFile("..\\inputs\\input_2020_9.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY09
