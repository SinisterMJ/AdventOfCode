#ifndef ADVENTOFCODE2022_DAY01
#define ADVENTOFCODE2022_DAY01

#include "../includes/aoc.h"
#include <algorithm>

class Day01 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::pair<int64_t, int64_t> solve()
    {
        int64_t cur_sum = 0;
        std::vector<int64_t> sums;

        for (auto line : inputVector)
        {
            if (line != "")
                cur_sum += std::stoi(line);
            else
            {
                sums.push_back(cur_sum);
                cur_sum = 0;
            }
        }

        std::nth_element(sums.begin(), sums.begin() + 3, sums.end(), std::greater{});

        return std::make_pair(sums[0], sums[0] + sums[1] + sums[2]);
    }

public:
    Day01()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_1.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY01