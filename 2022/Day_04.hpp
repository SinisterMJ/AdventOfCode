#ifndef ADVENTOFCODE2022_DAY04
#define ADVENTOFCODE2022_DAY04

#include "../includes/aoc.h"

class Day04 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;


    int64_t part1()
    {
        int count = 0;
        int total = 0;
        for (auto line : inputVector)
        {
            total++;
            auto splitted = util::split(line, ',');
            auto first = util::split(splitted[0], '-');
            auto second = util::split(splitted[1], '-');

            if (std::stoi(first[0]) <= std::stoi(second[0]) && std::stoi(first[1]) >= std::stoi(second[1]))
                count++;
            else
                if (std::stoi(second[0]) <= std::stoi(first[0]) && std::stoi(second[1]) >= std::stoi(first[1]))
                    count++;
        }

        return count;
    }

    int64_t part2()
    {
        int count = 0;
        
        for (auto line : inputVector)
        {
            auto splitted = util::split(line, ',');
            auto first = util::split(splitted[0], '-');
            auto second = util::split(splitted[1], '-');

            std::set<int32_t> local;

            for (int start = std::stoi(first[0]); start <= std::stoi(first[1]); ++start)
                local.insert(start);
            for (int start = std::stoi(second[0]); start <= std::stoi(second[1]); ++start)
            {
                if (local.contains(start))
                {
                    count++;
                    break;
                }
            }
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