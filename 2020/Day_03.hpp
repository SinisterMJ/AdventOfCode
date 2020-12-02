#ifndef ADVENTOFCODE2020_DAY03
#define ADVENTOFCODE2020_DAY03

#include "../includes/aoc.h"

class Day03 {
private:
	
	std::vector<std::string> inputs;
    std::string input;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\input_2020_3.txt");
        input = util::readFile("..\\inputs\\input_2020_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int result_1 = 0;
        int result_2 = 0;
        
        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY03