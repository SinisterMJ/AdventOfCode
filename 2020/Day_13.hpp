#ifndef ADVENTOFCODE2020_DAY13
#define ADVENTOFCODE2020_DAY13

#include "../includes/aoc.h"

class Day13 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day13()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_13.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_13.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY13
