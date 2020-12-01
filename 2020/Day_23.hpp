#ifndef ADVENTOFCODE2020_DAY23
#define ADVENTOFCODE2020_DAY23

#include "../includes/aoc.h"

class Day23 {
private:
	std::string inputString;
	
public:
	Day23()
	{
		inputString = util::readFile("..\\inputs\\input_2020_23.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY23
