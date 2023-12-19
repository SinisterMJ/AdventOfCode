#ifndef ADVENTOFCODE2023_DAY20
#define ADVENTOFCODE2023_DAY20

#include "../includes/aoc.h"
#include <algorithm>

class Day20 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        return 0;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day20()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_20.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_20.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 20 - Part 1: " << result_1 << '\n'
                  << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY20