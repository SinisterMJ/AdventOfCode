#ifndef ADVENTOFCODE2024_DAY01
#define ADVENTOFCODE2024_DAY01

#include "../includes/aoc.h"
#include <algorithm>

class Day01 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<int32_t> list_left;
    std::vector<int32_t> list_right;

    int64_t part1()
    {

        for (auto item : inputVector)
        {
            auto items = util::splitInt(item, ' ');
            list_left.push_back(items[0]);
            list_right.push_back(items[1]);
        }

        std::sort(list_left.begin(), list_left.end());
        std::sort(list_right.begin(), list_right.end());

        int result = 0;
        for (int index = 0; index < list_left.size(); ++index)
            result += std::abs(list_left[index] - list_right[index]);

        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;

        for (int i = 0; i < list_left.size(); ++i)
            for (int j = 0; j < list_right.size(); ++j)
                if (list_left[i] == list_right[j])
                    result += list_left[i];
                
        return result;
    }

public:
    Day01()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_1.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY01