#ifndef ADVENTOFCODE2025_DAY03
#define ADVENTOFCODE2025_DAY03

#include "../includes/aoc.h"
#include <algorithm>

class Day03 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int sum = 0;
        for (const std::string& line : inputVector)
        {
            auto first = std::max_element(line.begin(), line.end() - 1);
            auto second = std::max_element(first + 1, line.end());
            sum += (*first - '0') * 10 + (*second - '0');
        }

        return sum;
    }

    int64_t part2()
    {
        int64_t sum = 0;
        for (const std::string& line : inputVector)
        {
            int64_t joltage = 0;
            auto start = line.begin();
            for (int i = 0; i < 12; ++i)
            {
                auto val = std::max_element(start, line.end() - 11 + i);
                joltage = joltage * 10 + (*val - '0');
                start = val + 1;
            }

            sum += joltage;
        }

        return sum;
    }

public:
    Day03()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_3.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY03