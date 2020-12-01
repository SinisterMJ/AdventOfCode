#ifndef ADVENTOFCODE2020_DAY02
#define ADVENTOFCODE2020_DAY02

#include "../includes/aoc.h"

class Day02 {
private:
	std::string inputString;
public:
	Day02()
	{
		inputString = util::readFile("..\\inputs\\input_2020_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY02