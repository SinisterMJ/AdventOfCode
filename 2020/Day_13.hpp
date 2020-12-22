#ifndef ADVENTOFCODE2020_DAY13
#define ADVENTOFCODE2020_DAY13

#include "../includes/aoc.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <execution>
#include <utility>

class Day13 {
private:
    /*std::vector<int64_t> lines;
    std::vector<int64_t> times;*/

    std::vector<std::pair<int64_t, int64_t>> busLines;
    
    void ReadBusses()
    {
        auto buses = util::split(inputVec[1], ',');

        int index = 0;
        for (auto elem : buses)
        {
            if (elem != "x")
            {
                int64_t num = std::stoi(elem);
                int64_t modulo = (num - index) % num;
                while (modulo < 0)
                    modulo += num;

                busLines.push_back(std::make_pair(num, modulo));
            }
            index++;
        }

        std::sort(busLines.rbegin(), busLines.rend());
    }

    int64_t part1()
    {
        uint32_t depTime = std::stoi(inputVec[0]);

        for (int index = depTime; ; ++index)
        {
            for (auto elem : busLines)
            {
                if (index % elem.first == 0)
                {
                    return elem.first * (index - depTime);
                }
            }
        }
    }

    int64_t part2()
    {        
        int64_t prod = 1;
        int64_t pos = busLines[0].first;

        for (auto bus : busLines)
        {
            while (pos % bus.first != bus.second)
            {
                pos += prod;
            }

            prod *= bus.first;
        }

        return pos;
    }

    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day13()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_13.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_13.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        ReadBusses();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY13
