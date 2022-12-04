#ifndef ADVENTOFCODE2022_DAY04
#define ADVENTOFCODE2022_DAY04

#include "../includes/aoc.h"
#include <utility>

class Day04 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::pair<int64_t, int64_t> solve()
    {
        int64_t count_1 = 0;
        int64_t count_2 = 0;
     
        for (auto line : inputVector)
        {
            auto splitted = util::split(line, ',');
            auto first = util::split(splitted[0], '-');
            auto second = util::split(splitted[1], '-');

            if (in_range(std::stoi(second[0]), std::stoi(first[0]), std::stoi(first[1])) && in_range(std::stoi(second[1]), std::stoi(first[0]), std::stoi(first[1])) ||
                in_range(std::stoi(first[0]), std::stoi(second[0]), std::stoi(second[1])) && in_range(std::stoi(first[1]), std::stoi(second[0]), std::stoi(second[1])))
                count_1++;

            if (in_range(std::stoi(first[0]), std::stoi(second[0]), std::stoi(second[1])) ||
                in_range(std::stoi(second[0]), std::stoi(first[0]), std::stoi(first[1])))
                count_2++;
        }
        
        return std::make_pair(count_1, count_2);
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

        auto result = solve();
        auto result_1 = result.first;;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY04