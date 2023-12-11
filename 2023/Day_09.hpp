#ifndef ADVENTOFCODE2023_DAY09
#define ADVENTOFCODE2023_DAY09

#include "../includes/aoc.h"
#include <algorithm>

class Day09 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::pair<int64_t, int64_t> parts()
    {
        int64_t result_1 = 0;
        int64_t result_2 = 0;

        for (auto line : inputVector)
        {
            auto nums = util::splitInt(line, ' ');

            std::map<int, std::vector<int32_t>> levels;
            levels[0] = nums;

            int index = 0;

            bool allZeros = false;

            while (!allZeros)
            {
                std::vector<int32_t> newVals;
                for (int32_t i = 0; i < levels[index].size() - 1; ++i)
                    newVals.push_back(levels[index][i + 1] - levels[index][i]);

                levels[++index] = newVals;

                allZeros = std::all_of(levels[index].begin(), levels[index].end(), [](int i) { return i == 0; });
            }

            while (index > 0)
            {
                levels[index - 1].insert(levels[index - 1].begin(), (levels[index - 1][0] - levels[index][0]));
                levels[index - 1].push_back(levels[index - 1].back() + levels[index].back());
                --index;
            }

            result_1 += levels[0][levels[0].size() - 1];
            result_2 += levels[0][0];
        }

        return std::make_pair(result_1, result_2);
    }

public:
    Day09()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto results = parts();

        auto result_1 = results.first;
        auto result_2 = results.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY09