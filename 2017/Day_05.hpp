#ifndef ADVENTOFCODE2017_DAY05
#define ADVENTOFCODE2017_DAY05

#include "../includes/aoc.h"
#include <bitset>

class Day05 {
private:
    std::vector<std::string> inputs;
    std::string input;

    int64_t solve(bool greater_three) 
    {        
        int64_t result = 0;
        int32_t position = 0;

        auto commandList = util::ConvertToInt(inputs);

        while (position >= 0 && position < commandList.size())
        {
            int32_t command = commandList[position];

            if (command >= 3 && greater_three)
                commandList[position] -= 1;
            else
                commandList[position] += 1;

            position += command;
            ++result;
        }

        return result;
    }

public:
    Day05()
    {
        inputs = util::readFileLines("..\\inputs\\2017\\input_5.txt", '\n', false);
        input = util::readFile("..\\inputs\\2017\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = solve(false);
        int64_t result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout 
            << "Day 05 - Part 1: " << result_1 << '\n'
            << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY05
