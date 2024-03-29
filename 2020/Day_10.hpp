#ifndef ADVENTOFCODE2020_DAY10
#define ADVENTOFCODE2020_DAY10

#include "../includes/aoc.h"

class Day10 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<int64_t> adapters;

    int64_t getDifferences()
    {
        int64_t count[2];
        count[0] = 0;
        count[1] = 0;

        for (int index = 1; index < adapters.size(); ++index)
        {
            count[(adapters[index] - adapters[index - 1] - 1) / 2]++;
        }

        return count[0] * count[1];
    }

    int64_t getCountPerm() 
    {
        std::vector<int64_t> dp{ 1 };
        for (int32_t i = 1; i < adapters.size(); ++i)
        {
            int64_t ans = 0;
            for (int32_t j = 0; j < i; ++j)
            {
                if (adapters[j] + 3 >= adapters[i])
                    ans += dp[j];
            }
            dp.push_back(ans);
        }

        return dp.back();
    }

public:
    Day10()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_10.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_10.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        adapters = util::ConvertToInt64(inputVec);
        adapters.push_back(0);
        std::sort(adapters.begin(), adapters.end());
        adapters.push_back(adapters.back() + 3);
        
        auto result_1 = getDifferences();
        auto result_2 = getCountPerm();

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY10
