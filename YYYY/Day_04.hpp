#ifndef ADVENTOFCODEYYYY_DAY04
#define ADVENTOFCODEYYYY_DAY04

#include "../includes/aoc.h"
#include <algorithm>

class Day04 {
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
    Day04()
    {
        inputVector = util::readFileLines("..\\inputs\\YYYY\\input_4.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODEYYYY_DAY04