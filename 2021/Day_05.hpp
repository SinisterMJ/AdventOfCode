#ifndef ADVENTOFCODE2021_DAY05
#define ADVENTOFCODE2021_DAY05

#include "../includes/aoc.h"
#include <bitset>

class Day05 {
private:
    std::vector<std::string> inputs;
    std::string input;

public:
	Day05()
	{
        inputs = util::readFileLines("..\\inputs\\2021\\input_5.txt", '\n', false);
        input = util::readFile("..\\inputs\\2021\\input_5.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int32_t result_1 = 0;
        int32_t result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY05
