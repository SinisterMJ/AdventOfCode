#ifndef ADVENTOFCODE2025_DAY03
#define ADVENTOFCODE2025_DAY03

#include "../includes/aoc.h"
#include <algorithm>

class Day03 {
private:

    std::vector<std::string> inputVector;

    int64_t run(const int batteries_on)
    {
        int64_t sum = 0;
        for (const std::string& line : inputVector)
        {
            int64_t joltage = 0;
            auto start = line.begin();
            for (int i = 0; i < batteries_on; ++i)
            {
                auto val = std::max_element(start, line.end() - batteries_on + 1 + i);
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

        auto result_1 = run(2);
        auto result_2 = run(12);

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY03