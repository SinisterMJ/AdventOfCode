#ifndef ADVENTOFCODE2020_DAY07
#define ADVENTOFCODE2020_DAY07

#include "../includes/aoc.h"

class Day07 {
private:
	std::string inputString;
    std::vector<std::string> inputVec;
public:
	Day07()
	{
		inputString = util::readFile("..\\inputs\\input_2020_7.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_7.txt", '\n', true);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int32_t result_1 = 0;
        int32_t result_2 = 0;

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY07
