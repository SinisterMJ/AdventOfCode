#ifndef ADVENTOFCODEYYYY_DAY21
#define ADVENTOFCODEYYYY_DAY21

#include "../includes/aoc.h"
#include <algorithm>

class Day21 {
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
    Day21()
    {
        inputVector = util::readFileLines("..\\inputs\\YYYY\\input_21.txt");
        inputString = util::readFile("..\\inputs\\YYYY\\input_21.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODEYYYY_DAY21