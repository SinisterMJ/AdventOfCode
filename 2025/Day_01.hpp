#ifndef ADVENTOFCODE2025_DAY01
#define ADVENTOFCODE2025_DAY01

#include "../includes/aoc.h"
#include <algorithm>
#include <charconv>

class Day01 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    static inline int mod100(int x) {
        int r = x % 100;
        return r < 0 ? r + 100 : r;
    }

    int64_t part1()
    {
        int start = 50;
        int zeros = 0;
        for (const std::string& turn : inputVector)
        {
            int sign = turn[0] == 'L' ? -1 : 1;
            int count = 0;
            std::from_chars(turn.data() + 1, turn.data() + turn.size(), count);
            start += sign * count;
            start = mod100(start);

            zeros += start == 0;
        }
        return zeros;
    }

    int64_t part2()
    {
        int start = 50;
        int zeros = 0;
        for (const std::string& turn : inputVector)
        {
            int started_zero = (start == 0) ? 1 : 0;

            int sign = turn[0] == 'L' ? -1 : 1;
            int count = 0;
            std::from_chars(turn.data() + 1, turn.data() + turn.size(), count);
            start += sign * count;

            if (start <= 0)
                zeros += -start / 100 + 1 - started_zero;
            else
                zeros += start / 100;

            start = mod100(start);
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