#ifndef ADVENTOFCODE2023_DAY18
#define ADVENTOFCODE2023_DAY18

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day18 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t areaPolygon(std::vector<v2>& polygon)
    {
        int64_t totalCount = 0;
        int64_t perimeter = 0;
        for (int index = 0; index < polygon.size() - 1; ++index)
        {
            auto first = polygon[index];
            auto second = polygon[index + 1];

            totalCount += ((first.x + second.x) * (first.y - second.y));
            perimeter += (first - second).manhattan();
        }

        totalCount = std::abs(totalCount);

        return totalCount / 2 + perimeter / 2 + 1;
    }

    int64_t part1()
    {
        std::map<v2, std::string> dug_out;
        std::map<std::string, v2> dir_lookup{
            {"R", v2(1, 0)},
            {"L", v2(-1, 0)},
            {"U", v2(0, -1)},
            {"D", v2(0, 1)}
        };

        v2 current(0, 0);
        std::vector<v2> polygon;
        polygon.push_back(current);

        for (auto line : inputVector)
        {
            auto parts = util::split(line, ' ');
            auto dir = dir_lookup[parts[0]];
            auto count = std::stoi(parts[1]);
            current += dir * count;
            polygon.push_back(current);
        }

        return areaPolygon(polygon);
    }

    int64_t part2()
    {
        std::map<v2, std::string> dug_out;
        std::map<std::string, v2> dir_lookup{
            {"0", v2(1, 0)},
            {"1", v2(0, 1)},
            {"2", v2(-1, 0)},
            {"3", v2(0, -1)}
        };

        std::vector<v2> polygon;

        v2 current(0, 0);
        polygon.push_back(current);
        int64_t perimeter = 0;

        for (auto line : inputVector)
        {
            auto parts = util::split(line, ' ');
            auto code = parts[2].substr(2, 6);
            int64_t count = std::stoi(code.substr(0, 5), 0, 16);
            v2 dir = dir_lookup[code.substr(5, 1)];
            current += dir * count;
            polygon.push_back(current);
            perimeter += count;
        }

        return areaPolygon(polygon);
    }

public:
    Day18()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_18.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_18.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 18 - Part 1: " << result_1 << '\n'
                  << "Day 18 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY18