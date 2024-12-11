#ifndef ADVENTOFCODE2024_DAY11
#define ADVENTOFCODE2024_DAY11

#include "../includes/aoc.h"
#include <algorithm>

class Day11 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    
    int64_t getPower(int times)
    {
        int64_t result = 1;
        for (int i = 0; i < times; ++i)
            result *= 10;

        return result;
    }

    int64_t solve(int epochs, std::vector<int64_t> start)
    {
        std::map<int64_t, int64_t> stones;

        for (auto el : start)
            stones[el] = 1;

        for (int i = 0; i < epochs; ++i)
        {
            std::map<int64_t, int64_t> outcome;
            for (auto [stone, count] : stones)
            {
                auto dig = numDigits(stone);
                if (stone == 0)
                    outcome[1] += count;
                else if (dig % 2 == 0)
                {
                    int64_t front = stone / getPower(dig / 2);
                    int64_t back = stone % getPower(dig / 2);
                    outcome[front] += count;
                    outcome[back] += count;
                    continue;
                }
                else
                    outcome[2024 * stone] += count;
            }
            std::swap(stones, outcome);
        }

        int64_t result = 0;

        for (auto [stone, count] : stones)
            result += count;

        return result;
    }

public:
    Day11()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_11.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(25, util::splitInt64(inputVector[0], ' '));
        auto result_2 = solve(75, util::splitInt64(inputVector[0], ' '));

        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY11