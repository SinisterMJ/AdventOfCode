#ifndef ADVENTOFCODE2015_DAY01
#define ADVENTOFCODE2015_DAY01

#include "../includes/aoc.h"
#include <iostream>

class Day01 {
private:
    std::string input;
public:
	Day01()
	{
		input = util::readFile("..\\inputs\\2015\\input_1.txt");
	}

	int64_t run()
	{	
		util::Timer myTime;
		myTime.start();
        		
        auto result_1 = std::count(input.begin(), input.end(), '(') - std::count(input.begin(), input.end(), ')');
        auto result_2 = 0;

        for (int index = 0; index < input.size(); ++index)
        {
            result_2 += (input[index] == '(');
            result_2 -= (input[index] == ')');

            if (result_2 == -1)
            {
                result_2 = index + 1;
                break;
            }
        }

		int64_t time = myTime.usPassed();

		std::cout << "Day 01 - Part 1: " << result_1 << std::endl
				  << "Day 01 - Part 2: " << result_2 << std::endl;

		return time;
	}
};

#endif  // ADVENTOFCODE2015_DAY01