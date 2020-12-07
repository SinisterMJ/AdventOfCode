#ifndef ADVENTOFCODE2020_DAY25
#define ADVENTOFCODE2020_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day25()
    {
        inputString = util::readFile("..\\inputs\\input_2020_25.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_25.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        int64_t time = myTime.usPassed();
        std::cout << "Day 25 - Part 1: " << result_1 << '\n'
                  << "Day 25 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY25
