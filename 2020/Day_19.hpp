#ifndef ADVENTOFCODE2020_DAY19
#define ADVENTOFCODE2020_DAY19

#include "../includes/aoc.h"

class Day19 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day19()
    {
        inputString = util::readFile("..\\inputs\\input_2020_19.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_19.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 19 - Part 1: " << result_1 << '\n'
                  << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY19
