#ifndef ADVENTOFCODE2019_DAY17
#define ADVENTOFCODE2019_DAY17

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day17 {
private:
	std::vector<std::string> inputVector;
	std::string inputString;
public:
	Day17()
	{
		inputString = util::readFile("..\\inputs\\input_2019_17.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2019_17.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		int64_t result1 = 0;
		int64_t result2 = 0;

		std::cout << "Day 17 - Part 1: " << result1 << std::endl
				  << "Day 17 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY17