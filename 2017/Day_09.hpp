#ifndef ADVENTOFCODE2017_DAY09
#define ADVENTOFCODE2017_DAY09

#include "../includes/aoc.h"

class Day09 {
private:
    std::string inputString;

    std::pair<int64_t, int64_t> solve()
    {
        int64_t sum = 0;
        int64_t trashCount = 0;
        int64_t current_depth = 0;

        bool trash = false;
        bool ignoreNext = false;

        for (auto& ch : inputString)
        {
            if (ignoreNext)
            {
                ignoreNext = false;
                continue;
            }

            if (ch == '!')
                ignoreNext = true;

            if (ch == '>')
                trash = false;

            if (trash && ch != '!')
            {
                trashCount++;
                continue;
            }

            if (ch == '<')
                trash = true;

            if (ch == '{')
                ++current_depth;
            
            if (ch == '}')
            {
                sum += current_depth;
                --current_depth;
            }
        }

        return std::make_pair(sum, trashCount);
    }

public:
    Day09()
    {
        inputString = util::readFile("..\\inputs\\2017\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto res = solve();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 09 - Part 1: " << result_1 << '\n'
            << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
