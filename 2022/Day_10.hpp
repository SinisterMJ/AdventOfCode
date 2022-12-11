#ifndef ADVENTOFCODE2022_DAY10
#define ADVENTOFCODE2022_DAY10

#include "../includes/aoc.h"

class Day10 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int cycle = 1;
        int64_t sum = 0;
        int64_t x = 1;
        for (auto line : inputVector)
        {
            if (line == "noop")
            {
                cycle++;
                if ((cycle + 20) % 40 == 0 && cycle < 230)
                    sum += cycle * x;
                continue;
            }

            auto cmd = util::split(line, ' ');
            cycle++;

            if ((cycle + 20) % 40 == 0 && cycle < 230)
                sum += cycle * x;
            
            cycle++;
            x += std::stoi(cmd[1]);
            
            if ((cycle + 20) % 40 == 0 && cycle < 230)
                sum += cycle * x;
        }
        return sum;
    }

    std::string draw_function(int cycle, int x)
    {
        std::string result = "";
        if (in_range(x, ((cycle - 1) % 40) - 1, ((cycle - 1) % 40) + 1))
            result += "#";
        else
            result += " ";

        if (cycle % 40 == 0)
            result += "\n";

        return result;
    }

    std::string part2()
    {
        int cycle = 1;
        int x = 1;
        std::string result = "\n";
        for (auto line : inputVector)
        {
            if (line == "noop")
            {
                result += draw_function(cycle++, x);
                continue;
            }

            auto cmd = util::split(line, ' ');
            result += draw_function(cycle++, x);
            result += draw_function(cycle++, x);
            x += std::stoi(cmd[1]);
        }
        return result;
    }

public:
    Day10()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_10.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_10.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY10