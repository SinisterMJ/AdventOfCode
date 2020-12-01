#ifndef ADVENTOFCODE2020_DAY20
#define ADVENTOFCODE2020_DAY20

#include "../includes/aoc.h"

class Day20 {
private:
	std::string inputString;
	std::vector<std::string> inputVector;
	
public:
	Day20()
	{
		inputString = util::readFile("..\\inputs\\input_2020_20.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2020_20.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY2
