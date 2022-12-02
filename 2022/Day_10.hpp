#ifndef ADVENTOFCODE2022_DAY10
#define ADVENTOFCODE2022_DAY10

#include "../includes/aoc.h"

class Day10 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

public:
    Day10()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_10.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_10.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = 0;
        auto result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY10