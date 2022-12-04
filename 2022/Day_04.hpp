#ifndef ADVENTOFCODE2022_DAY04
#define ADVENTOFCODE2022_DAY04

#include "../includes/aoc.h"

class Day04 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<std::array<std::array<int32_t, 2>, 2>> ids;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            auto splitted = util::split(line, ',');
            auto first = util::split(splitted[0], '-');
            auto second = util::split(splitted[1], '-');

            std::array<std::array<int32_t, 2>, 2> temp;
            temp[0] = std::array<int32_t, 2>();
            temp[0][0] = std::stoi(first[0]);
            temp[0][1] = std::stoi(first[1]);
            temp[1][0] = std::stoi(second[0]);
            temp[1][1] = std::stoi(second[1]);
            ids.push_back(temp);
        }

        int count = 0;
        for (auto id : ids)
        {
            if (in_range(id[1][0], id[0][0], id[0][1]) && in_range(id[1][1], id[0][0], id[0][1]) ||
                in_range(id[0][0], id[1][0], id[1][1]) && in_range(id[0][1], id[1][0], id[1][1]))
                count++;
        }
        
        return count;
    }

    int64_t part2()
    {
        int count = 0;
        
        for (auto id : ids)
        {
            if (in_range(id[0][0], id[1][0], id[1][1]) ||
                in_range(id[1][0], id[0][0], id[0][1]))
                count++;
        }

        return count;
    }

public:
    Day04()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_4.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_4.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY04