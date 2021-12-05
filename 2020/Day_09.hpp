#ifndef ADVENTOFCODE2020_DAY09
#define ADVENTOFCODE2020_DAY09

#include "../includes/aoc.h"
#include <algorithm>
#include <numeric>

class Day09 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<int64_t> inputs;

    int64_t part1()
    {
        for (int index = 25; index < inputs.size(); ++index)
        {
            bool found = false;
            for (int i = index - 25; i < index && !found; ++i)
            {
                auto it = std::find(
                    inputs.begin() + i + 1,
                    inputs.begin() + index,
                    inputs[index] - inputs[i]);

                found |= (it != (inputs.begin() + index));
            }

            if (!found)
                return inputs[index];
        }

        return -1;
    }

    int64_t part2(int64_t test)
    {
        int start = 0;
        int end = 1;
        int64_t acc = inputs[start] + inputs[end];
        for (;start < end && end < inputs.size();)
        {
            if (acc < test)
            {
                end++;
                acc += inputs[end];
            }

            if (acc > test)
            {
                acc -= inputs[start];
                start++;
            }

            if (acc == test)
            {
                int64_t min = std::numeric_limits<int64_t>::max();
                int64_t max = 0;
                for (int k = start; k <= end; ++k)
                {
                    min = std::min(min, inputs[k]);
                    max = std::max(max, inputs[k]);
                }

                return min + max;
            }
        }

        return -1;
    }

public:
    Day09()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_9.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_9.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        inputs = util::ConvertToInt64(inputVec);

        auto result_1 = part1();
        auto result_2 = part2(result_1);

        int64_t time = myTime.usPassed();
        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY09
