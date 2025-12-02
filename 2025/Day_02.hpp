#ifndef ADVENTOFCODE2025_DAY02
#define ADVENTOFCODE2025_DAY02

#include "../includes/aoc.h"
#include <algorithm>

class Day02 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int64_t result = 0;
        for (const std::string& line : util::split(inputVector[0], ','))
        {
            auto ranges = util::splitInt64(line, '-');
            for (int64_t i = ranges[0]; i <= ranges[1]; ++i)
            {
                auto str = std::to_string(i);
                if (str.size() % 2 == 1)
                    continue;
                
                if (str.substr(0, str.size() / 2) == str.substr(str.size() / 2))
                    result += i;
            }
        }
        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;
        for (const std::string& line : util::split(inputVector[0], ','))
        {
            auto ranges = util::splitInt64(line, '-');
            for (int64_t i = ranges[0]; i <= ranges[1]; ++i)
            {
                auto str = std::to_string(i);
                
                if ((str + str).find(str, 1) < str.size())
                    result += i;
            }
        }
        return result;
    }

public:
    Day02()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_2.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << '\n'
                  << "Day 02 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY02