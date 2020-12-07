#ifndef ADVENTOFCODE2020_DAY15
#define ADVENTOFCODE2020_DAY15

#include "../includes/aoc.h"

class Day15 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day15()
    {
        inputString = util::readFile("..\\inputs\\input_2020_15.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_15.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY15
