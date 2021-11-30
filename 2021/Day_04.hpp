#ifndef ADVENTOFCODE2021_DAY04
#define ADVENTOFCODE2021_DAY04

#include "../includes/aoc.h"
#include <regex>

class Day04 {
private:

	std::vector<std::string> inputs;
    std::string input;

public:    
	Day04()
	{
		inputs = util::readFileLines("..\\inputs\\2021\\input_4.txt", '\n', false);
        input = util::readFile("..\\inputs\\2021\\input_4.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
              
        int64_t result_1 = 0;
        int64_t result_2 = 0;
        
        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY04