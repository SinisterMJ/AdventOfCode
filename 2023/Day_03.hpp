#ifndef ADVENTOFCODE2023_DAY03
#define ADVENTOFCODE2023_DAY03

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <unordered_map>

#include <algorithm>

class Day03 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::unordered_map<v2, int8_t> engine;
        auto neighbours = MapHelper::getNeighboursVec(true);

        int x = 0;
        int y = 0;

        int result = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                engine[v2(x, y)] = ch;
                x++;
            }
            x = 0;
            y++;
        }

        for (auto [pos, val] : engine)
        {
            if (val != '.' && !in_range<int8_t>(val, '0', '9'))
            {
                for (auto n : neighbours)
                {
                    if (engine.find(n + pos) != engine.end() && in_range<int8_t>(engine[n + pos], '0', '9'))
                    {
                        std::string start = std::string(1, engine[n + pos]);
                        engine[n] = '.';

                        int index = 1;
                        while (engine.find(n + pos + v2(1, 0) * index) != engine.end() && in_range<int8_t>(engine[n + pos + v2(1, 0) * index], '0', '9'))
                        {
                            start += std::string(1, engine[n + pos + v2(1, 0) * index]);
                            engine[n + pos + v2(1, 0) * index] = '.';
                            index++;
                        }

                        index = 1;
                        while (engine.find(n + pos + v2(-1, 0) * index) != engine.end() && in_range<int8_t>(engine[n + pos + v2(-1, 0) * index], '0', '9'))
                        {
                            start = std::string(1, engine[n + pos + v2(-1, 0) * index]) + start;
                            engine[n + pos + v2(-1, 0) * index] = '.';
                            index++;
                        }

                        result += std::stoi(start);
                    }
                }
            }
        }

        return result;
    }

    int64_t part2()
    {

        std::unordered_map<v2, int8_t> engine;
        auto neighbours = MapHelper::getNeighboursVec(true);

        int x = 0;
        int y = 0;

        int result = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                engine[v2(x, y)] = ch;
                x++;
            }
            x = 0;
            y++;
        }

        for (auto [pos, val] : engine)
        {
            if (val == '*')
            {
                std::vector<std::string> adjacent;
                for (auto n : neighbours)
                {
                    if (engine.find(n + pos) != engine.end() && in_range<int8_t>(engine[n + pos], '0', '9'))
                    {
                        std::string start = std::string(1, engine[n + pos]);
                        engine[n] = '.';

                        int index = 1;
                        while (engine.find(n + pos + v2(1, 0) * index) != engine.end() && in_range<int8_t>(engine[n + pos + v2(1, 0) * index], '0', '9'))
                        {
                            start += std::string(1, engine[n + pos + v2(1, 0) * index]);
                            engine[n + pos + v2(1, 0) * index] = '.';
                            index++;
                        }

                        index = 1;
                        while (engine.find(n + pos + v2(-1, 0) * index) != engine.end() && in_range<int8_t>(engine[n + pos + v2(-1, 0) * index], '0', '9'))
                        {
                            start = std::string(1, engine[n + pos + v2(-1, 0) * index]) + start;
                            engine[n + pos + v2(-1, 0) * index] = '.';
                            index++;
                        }

                        adjacent.push_back(start);
                    }
                }

                if (adjacent.size() == 2)
                {
                    result += std::stoi(adjacent[0]) * std::stoi(adjacent[1]);
                }
            }
        }

        return result;
    }

public:
    Day03()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_3.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY03