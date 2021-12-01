#ifndef ADVENTOFCODE2021_DAY08
#define ADVENTOFCODE2021_DAY08

#include "../includes/aoc.h"

class Day08 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;

public:
    Day08()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_8.txt");
        inputVector = util::readFileLines("..\\inputs\\2021\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int32_t result_1 = 0;
        int32_t result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY08