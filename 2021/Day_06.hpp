#ifndef ADVENTOFCODE2021_DAY06
#define ADVENTOFCODE2021_DAY06

#include "../includes/aoc.h"

class Day06 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;

public:
    Day06()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_6.txt");
        inputVector = util::readFileLines("..\\inputs\\2021\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int32_t result_1 = 0;
        int32_t result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY06