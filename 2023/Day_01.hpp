#ifndef ADVENTOFCODE2023_DAY01
#define ADVENTOFCODE2023_DAY01

#include "../includes/aoc.h"
#include <algorithm>

class Day01 {
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
    Day01()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_1.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY01