#ifndef ADVENTOFCODE2020_DAY22
#define ADVENTOFCODE2020_DAY22

#include "../includes/aoc.h"

class Day22 {
private:
	std::string inputString;
	std::vector<std::string> inputVector;
	
public:
	Day22()
	{
		inputString = util::readFile("..\\inputs\\input_2020_22.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2020_22.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY22
