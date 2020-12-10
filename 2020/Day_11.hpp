#ifndef ADVENTOFCODE2020_DAY11
#define ADVENTOFCODE2020_DAY11

#include "../includes/aoc.h"

class Day11 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day11()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY11
