#ifndef ADVENTOFCODE2020_DAY21
#define ADVENTOFCODE2020_DAY21

#include "../includes/aoc.h"

class Day21 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day21()
    {
        inputString = util::readFile("..\\inputs\\input_2020_21.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_21.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY21
