#ifndef ADVENTOFCODE2024_DAY05
#define ADVENTOFCODE2024_DAY05

#include "../includes/aoc.h"
#include <algorithm>

class Day05 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<int32_t, std::vector<int32_t>> rules;
    std::vector<std::vector<int32_t>> prints;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            if (line.find("|") != std::string::npos)
            {
                auto nums = util::splitInt(line, '|');

                if (rules.find(nums[0]) == rules.end())
                    rules[nums[0]] = std::vector<int32_t>();

                rules[nums[0]].push_back(nums[1]);
            }

            if (line.find(",") != std::string::npos)
            {
                auto nums = util::splitInt(line, ',');
                std::vector<int32_t> local;
                for (auto num : nums)
                    local.push_back(num);

                prints.push_back(nums);
            }
        }

        int64_t result = 0;

        for (auto print : prints)
        {
            bool good = true;
            for (int i = 0; i < print.size(); ++i)
            {
                for (int j = i + 1; j < print.size(); ++j)
                {
                    if (std::find(rules[print[j]].begin(), rules[print[j]].end(), print[i]) != rules[print[j]].end())
                        good = false;
                }
            }

            if (good)
                result += print[print.size() / 2];
        }

        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;

        for (auto print : prints)
        {
            bool good = true;
            for (int i = 0; i < print.size(); ++i)
            {
                for (int j = i + 1; j < print.size(); ++j)
                {
                    if (std::find(rules[print[j]].begin(), rules[print[j]].end(), print[i]) != rules[print[j]].end())
                        good = false;
                }
            }

            if (good)
                continue;

            while (!good)
            {
                good = true;
                for (int i = 0; i < print.size(); ++i)
                {
                    for (int j = i + 1; j < print.size(); ++j)
                    {
                        if (std::find(rules[print[j]].begin(), rules[print[j]].end(), print[i]) != rules[print[j]].end())
                        {
                            good = false;
                            std::swap(print[i], print[j]);
                        }
                    }
                }
            }

            result += print[print.size() / 2];
        }

        return result;
    }

public:
    Day05()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY05