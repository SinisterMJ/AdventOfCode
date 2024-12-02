#ifndef ADVENTOFCODE2024_DAY02
#define ADVENTOFCODE2024_DAY02

#include "../includes/aoc.h"
#include <algorithm>

class Day02 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int save = 0;
        for (auto line : inputVector)
        {
            auto values = util::splitInt(line, ' ');
            bool line_save = true;
            bool ascending = values[0] < values[1];
            for (int i = 1; i < values.size(); ++i)
            {
                if (!in_range(std::abs(values[i] - values[i - 1]), 1, 3))
                    line_save = false;

                if ((values[i - 1] < values[i]) != ascending)
                    line_save = false;
            }

            save += line_save;
        }
        return save;
    }

    int64_t part2()
    {
        int save = 0;
        for (auto line : inputVector)
        {
            auto values = util::splitInt(line, ' ');

            bool fix_found = false;
            for (int index = 0; index < values.size(); ++index)
            {
                auto copy = values;
                copy.erase(copy.begin() + index);

                bool line_save = true;
                bool ascending = copy[0] < copy[1];
                for (int i = 1; i < copy.size(); ++i)
                {
                    if (!in_range(std::abs(copy[i] - copy[i - 1]), 1, 3))
                        line_save = false;

                    if ((copy[i - 1] < copy[i]) != ascending)
                        line_save = false;
                }

                fix_found |= line_save;
                if (fix_found)
                    break;
            }            

            save += fix_found;
        }
        return save;
    }

public:
    Day02()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_2.txt");
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

#endif  // ADVENTOFCODE2024_DAY02