#ifndef ADVENTOFCODE2023_DAY23
#define ADVENTOFCODE2023_DAY23

#include "../includes/aoc.h"
#include <algorithm>

class Day23 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int part1()
    {
        return 0;
    }

    int part2()
    {
        return 0;
    }

public:
    Day23()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_23.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_23.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
                  << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY23