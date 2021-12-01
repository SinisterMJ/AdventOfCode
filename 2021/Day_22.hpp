#ifndef ADVENTOFCODE2021_DAY22
#define ADVENTOFCODE2021_DAY22

#include "../includes/aoc.h"

class Day22 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<int64_t> adapters;

    int64_t part1()
    {
        return 0;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day22()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_22.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_22.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        adapters = util::ConvertToInt64(inputVec);

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 22 - Part 1: " << result_1 << '\n'
            << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
