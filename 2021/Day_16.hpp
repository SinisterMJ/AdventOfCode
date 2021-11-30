#ifndef ADVENTOFCODE2021_DAY16
#define ADVENTOFCODE2021_DAY16

#include "../includes/aoc.h"
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

class Day16 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        return 0;
    }

    int64_t part2() 
    {
        return 0;
    }

public:
    Day16()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_16.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_16.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
                
        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY16
