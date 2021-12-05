#ifndef ADVENTOFCODE2021_DAY19
#define ADVENTOFCODE2021_DAY19

#include "../includes/aoc.h"

class Day19 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        return 0;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day19()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_19.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_19.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 19 - Part 1: " << result_1 << '\n'
            << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
