#ifndef ADVENTOFCODE2021_DAY01
#define ADVENTOFCODE2021_DAY01

#include "../includes/aoc.h"
#include <algorithm>
#include <iostream>

class Day01 {
private:
	
	std::vector<std::string> inputVector;
	std::string inputString;

public:
	Day01()
	{
		inputVector = util::readFileLines("..\\inputs\\2021\\input_1.txt");
		inputString = util::readFile("..\\inputs\\2021\\input_1.txt");
	}

	int64_t run()
	{
		std::vector<int32_t> numbers = util::ConvertToInt(inputVector);

		util::Timer myTime;
		myTime.start();

		int result_1 = -1;
		int result_2 = -1;

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

		return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY01