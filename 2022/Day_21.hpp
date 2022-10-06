#ifndef ADVENTOFCODE2022_DAY21
#define ADVENTOFCODE2022_DAY21

#include "../includes/aoc.h"

class Day21 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

public:
    Day21()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_21.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_21.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = 0;
        auto result_2 = 0;

        int64_t time = myTime.usPassed();

        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY21