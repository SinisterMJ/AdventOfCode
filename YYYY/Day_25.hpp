#ifndef ADVENTOFCODEYYYY_DAY25
#define ADVENTOFCODEYYYY_DAY25

#include "../includes/aoc.h"
#include <algorithm>

class Day25 {
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
    Day25()
    {
        inputVector = util::readFileLines("..\\inputs\\YYYY\\input_25.txt");
        inputString = util::readFile("..\\inputs\\YYYY\\input_25.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 25 - Part 1: " << result_1 << '\n'
                  << "Day 25 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODEYYYY_DAY25