#ifndef ADVENTOFCODE2022_DAY06
#define ADVENTOFCODE2022_DAY06

#include "../includes/aoc.h"

class Day06 {
private:

    std::string inputString;

    int32_t solve(int32_t count)
    {
        for (int index = 0; index < inputString.size() - count; index++)
        {
            bool found_candidate = true;
            for (int i = index; i < index + count && found_candidate; ++i)
            {
                for (int j = i + 1; j < index + count; ++j)
                {
                    found_candidate &= inputString[i] != inputString[j];
                    if (inputString[i] == inputString[j])
                    {
                        // Skip ahead by offset i
                        index += i - index;
                        break;
                    }
                }
            }

            if (found_candidate)
                return index + count;
        }
        return 0;
    }

public:
    Day06()
    {
        inputString = util::readFile("..\\inputs\\2022\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(4);
        auto result_2 = solve(14);

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY06