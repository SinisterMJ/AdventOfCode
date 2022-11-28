#ifndef ADVENTOFCODE2016_DAY11
#define ADVENTOFCODE2016_DAY11

#include "../includes/aoc.h"

class Day11 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

public:
    Day11()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_11.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_11.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = 0;
        auto result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
            << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY11