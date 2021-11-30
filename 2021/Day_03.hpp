#ifndef ADVENTOFCODE2021_DAY03
#define ADVENTOFCODE2021_DAY03

#include "../includes/aoc.h"

class Day03 {
private:
	
	std::vector<std::string> inputs;
    std::string input;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\2021\\input_3.txt");
        input = util::readFile("..\\inputs\\2021\\input_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;
                
        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY03