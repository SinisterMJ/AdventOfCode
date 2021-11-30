#ifndef ADVENTOFCODE2021_DAY25
#define ADVENTOFCODE2021_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

public:
    Day25()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_25.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_25.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 25 - Part 1: " << result_1 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY25
