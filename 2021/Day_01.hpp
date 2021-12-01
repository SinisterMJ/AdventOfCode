#ifndef ADVENTOFCODE2021_DAY01
#define ADVENTOFCODE2021_DAY01

#include "../includes/aoc.h"
#include <algorithm>
#include <iostream>

class Day01 {
private:
	
	std::vector<std::string> inputVector;
	std::string inputString;
    std::vector<int64_t> numbers;

    int64_t part1()
    {
        int count = 0;
        for (int i = 1; i < numbers.size(); i++)
        {
            if (numbers[i] > numbers[i - 1])
                count++;
        }

        return count;
    }

    int64_t part2()
    {
        int count = 0;
        for (int i = 3; i < numbers.size(); i++)
        {
            if (numbers[i] > numbers[i - 3])
                count++;
        }

        return count;
    }

public:
	Day01()
	{
		inputVector = util::readFileLines("..\\inputs\\2021\\input_1.txt");
		inputString = util::readFile("..\\inputs\\2021\\input_1.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        numbers = util::ConvertToInt64(inputVector);
        
		int64_t result_1 = part1();
		int64_t result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

		return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY01