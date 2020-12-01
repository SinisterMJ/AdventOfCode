#ifndef ADVENTOFCODE2020_DAY17
#define ADVENTOFCODE2020_DAY17

#include <map>

#include "../includes/aoc.h"

class Day17 {
private:
	std::vector<std::string> inputVector;
	std::string inputString;

public:
	Day17()
	{
		inputString = util::readFile("..\\inputs\\input_2020_17.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2020_17.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY17
