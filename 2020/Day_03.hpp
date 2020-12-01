#ifndef ADVENTOFCODE2020_DAY03
#define ADVENTOFCODE2020_DAY03

#include "../includes/aoc.h"

class Day03 {
private:
	
	std::vector<std::string> inputs;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\input_2020_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY03