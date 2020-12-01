#ifndef ADVENTOFCODE2020_DAY24
#define ADVENTOFCODE2020_DAY24

#include "../includes/aoc.h"

class Day24 {
private:
	std::string inputString;
	
public:
	Day24()
	{
		inputString = util::readFile("..\\inputs\\input_2020_24.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY24
