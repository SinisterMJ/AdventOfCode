#ifndef ADVENTOFCODE2017_DAY11
#define ADVENTOFCODE2017_DAY11

#include "../includes/aoc.h"

class Day11 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    
    std::vector<v2> neighbours{ v2(1, 0), v2(1, 1), v2(0, 1), v2(-1, 0), v2(-1, -1), v2(0, -1) };
    enum Direction {
        east,
        southeast,
        southwest,
        west,
        northwest,
        northeast
    };

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
        inputString = util::readFile("..\\inputs\\2017\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2017\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout 
            << "Day 11 - Part 1: " << result_1 << '\n'
            << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY11