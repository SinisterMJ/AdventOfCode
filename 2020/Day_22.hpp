#ifndef ADVENTOFCODE2020_DAY22
#define ADVENTOFCODE2020_DAY22

#include "../includes/aoc.h"

class Day22 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day22()
    {
        inputString = util::readFile("..\\inputs\\input_2020_22.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_22.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 22 - Part 1: " << result_1 << '\n'
                  << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY22
