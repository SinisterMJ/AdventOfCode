#ifndef ADVENTOFCODE2025_DAY15
#define ADVENTOFCODE2025_DAY15

#include "../includes/aoc.h"
#include <algorithm>

class Day15 {
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
    Day15()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_15.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY15