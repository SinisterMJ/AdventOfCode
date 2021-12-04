#ifndef ADVENTOFCODE2017_DAY01
#define ADVENTOFCODE2017_DAY01

#include "../includes/aoc.h"
#include <iostream>

class Day01 {
private:
    std::string input;

    int64_t part1_2(int offset)
    {
		int64_t result = 0;
		for (int i = 0; i < input.length(); ++i)
		{
			int j = i + offset;
			if (j >= input.length())
				j -= input.length();

			if (input[i] == input[j])
				result += input[i] - '0';
		}

		return result;
    }

public:
	Day01()
	{
		input = util::readFile("..\\inputs\\2017\\input_1.txt");
	}

	int64_t run()
	{	
		util::Timer myTime;
		myTime.start();

        int64_t result_1 = part1_2(1);
        int64_t result_2 = part1_2(input.length() / 2);

		int64_t time = myTime.usPassed();

		std::cout << "Day 01 - Part 1: " << result_1 << std::endl
				  << "Day 01 - Part 2: " << result_2 << std::endl;

		return time;
	}
};

#endif  // ADVENTOFCODE2017_DAY01