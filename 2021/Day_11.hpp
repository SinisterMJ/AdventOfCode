#ifndef ADVENTOFCODE2021_DAY11
#define ADVENTOFCODE2021_DAY11

#include "../includes/aoc.h"

class Day11 {
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
    Day11()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        adapters = util::ConvertToInt64(inputVec);

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY11