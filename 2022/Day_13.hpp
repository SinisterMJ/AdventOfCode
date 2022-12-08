#ifndef ADVENTOFCODE2022_DAY13
#define ADVENTOFCODE2022_DAY13

#include "../includes/aoc.h"

class Day13 {
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
    Day13()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_13.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY13