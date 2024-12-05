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

    std::pair<int64_t, int64_t> parts()
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

        int64_t result_1 = 0;
        int64_t result_2 = 0;

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
                result_1 += print[print.size() / 2];
            
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

                if (good)
                    result_2 += print[print.size() / 2];
            }            
        }

        return std::make_pair(result_1, result_2);
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

        auto result = parts();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY05