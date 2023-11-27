#ifndef ADVENTOFCODEYYYY_DAY18
#define ADVENTOFCODEYYYY_DAY18

#include "../includes/aoc.h"
#include <algorithm>

class Day18 {
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
    Day18()
    {
        inputVector = util::readFileLines("..\\inputs\\YYYY\\input_18.txt");
        inputString = util::readFile("..\\inputs\\YYYY\\input_18.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 18 - Part 1: " << result_1 << '\n'
                  << "Day 18 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODEYYYY_DAY18