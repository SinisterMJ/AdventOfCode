#ifndef ADVENTOFCODE2022_DAY16
#define ADVENTOFCODE2022_DAY16

#include "../includes/aoc.h"

class Day16 {
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
    Day16()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_16.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_16.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY16