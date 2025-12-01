#ifndef ADVENTOFCODE2025_DAY01
#define ADVENTOFCODE2025_DAY01

#include "../includes/aoc.h"
#include <algorithm>

class Day01 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int start = 50;
        int zeros = 0;
        for (auto turn : inputVector)
        {
            int sign = turn[0] == 'L' ? -1 : 1;
            int count = std::stoi(turn.substr(1));
            start += sign * count;
            start = (start % 100 + 100) % 100;

            if (start == 0)
            {
                zeros++;
            }
        }
        return zeros;
    }

    int64_t part2()
    {
        int start = 50;
        int zeros = 0;
        int lineCount = 0;
        bool started_zero = false;
        for (auto turn : inputVector)
        {
            started_zero = false;
            if (start == 0)
                started_zero = true;

            int sign = turn[0] == 'L' ? -1 : 1;
            int count = std::stoi(turn.substr(1));
            start += sign * count;

            if (start >= 100)
                zeros += start / 100;

            if (start <= 0)
                zeros += -start / 100 + 1 - started_zero;

            start = (start % 100 + 100) % 100;
        }
        return zeros;
    }

public:
    Day01()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_1.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY01