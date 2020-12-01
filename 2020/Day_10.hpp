#ifndef ADVENTOFCODE2020_DAY10
#define ADVENTOFCODE2020_DAY10

#include "../includes/aoc.h"

class Day10 {
private:
	std::vector<std::string> input;
public:
	Day10()
	{
		input = util::readFileLines("..\\inputs\\input_2020_10.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY10
