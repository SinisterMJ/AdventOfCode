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
        int64_t paths = 1;
        int32_t cur_1 = 0;

        for (int index = 1; index < adapters.size(); ++index)
        {
            if (adapters[index] - adapters[index - 1] == 1)
            {
                cur_1++;
            }
            if (adapters[index] - adapters[index - 1] == 3)
            {
                if (cur_1 == 0)
                    continue;

                paths *= static_cast<int32_t>(std::pow(2, cur_1 - 1)) - (cur_1 == 4);
                cur_1 = 0;
            }
        }

        return paths;
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
        
        int64_t result_1 = getDifferences();
        int64_t result_2 = getCountPerm();

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY10
