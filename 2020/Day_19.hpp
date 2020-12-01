#ifndef ADVENTOFCODE2020_DAY19
#define ADVENTOFCODE2020_DAY19

#include "../includes/aoc.h"

class Day19 {
private:
	std::string inputString;
	
public:
	Day19()
	{
		inputString = util::readFile("..\\inputs\\input_2020_19.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY19
