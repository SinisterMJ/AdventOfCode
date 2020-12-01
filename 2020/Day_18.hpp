#ifndef ADVENTOFCODE2020_DAY18
#define ADVENTOFCODE2020_DAY18

#include "../includes/aoc.h"

class Day18 {
private:
	std::string inputString;
	std::vector<std::string> inputVector;
	
public:
	Day18()
	{
		inputString = util::readFile("..\\inputs\\input_2020_18.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2020_18.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY18
