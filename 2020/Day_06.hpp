#ifndef ADVENTOFCODE2020_DAY06
#define ADVENTOFCODE2020_DAY06

#include "../includes/aoc.h"

class Day06 {
private:
	std::vector<std::string> inputString;
public:
	Day06()
	{
		inputString = inputString = util::readFileLines("..\\inputs\\input_2020_6.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY06
