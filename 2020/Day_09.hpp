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
            for (int i = index - 25; i < index; ++i)
            {
                for (int j = i + 1; j < index && !found; ++j)
                {
                    if (inputs[i] + inputs[j] == inputs[index])
                        found = true;
                }
            }

            if (!found)
                return inputs[index];
        }

        return -1;
    }

    int64_t part2(int64_t test)
    {
        for (int index = 1; index < inputs.size(); ++index)
        {
            int i = index - 1;
            int j = index;

            int acc = inputs[i] + inputs[j];

            while (true) {
                if (acc < test && i > 0)
                {
                    i--;
                    acc += inputs[i];
                }

                if (acc > test && j > i)
                {
                    acc -= inputs[j];
                    j--;
                }

                if (acc == test)
                {
                    int64_t min = std::numeric_limits<int64_t>::max();
                    int64_t max = 0;
                    for (int k = i; k <= j; ++k)
                    {
                        min = std::min(min, inputs[k]);
                        max = std::max(max, inputs[k]);
                    }

                    return min + max;
                }

                if (i == 0)
                    break;
            }
        }

        return -1;
    }
public:
    Day09()
    {
        inputString = util::readFile("..\\inputs\\input_2020_9.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_9.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        inputs = util::ConvertToInt64(inputVec);

        int64_t result_1 = part1();
        int64_t result_2 = part2(result_1);

        int64_t time = myTime.usPassed();
        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY09
