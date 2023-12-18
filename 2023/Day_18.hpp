#ifndef ADVENTOFCODE2023_DAY18
#define ADVENTOFCODE2023_DAY18

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day18 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int part1()
    {
        std::map<v2, std::string> dug_out;
        std::map<std::string, v2> dir_lookup{
            {"R", v2(1, 0)},
            {"L", v2(-1, 0)},
            {"U", v2(0, -1)},
            {"D", v2(0, 1)}
        };

        v2 current(0, 0);
        dug_out[current] = "...";

        for (auto line : inputVector)
        {
            auto parts = util::split(line, ' ');
            auto direction = parts[0];
            auto count = std::stoi(parts[1]);

            auto color = parts[2];

            for (int i = 0; i < count; ++i)
            {
                current += dir_lookup[direction];
                dug_out[current] = color;
            }
        }

        int64_t max_x = std::numeric_limits<int64_t>::min();
        int64_t max_y = std::numeric_limits<int64_t>::min();

        int64_t min_x = std::numeric_limits<int64_t>::max();
        int64_t min_y = std::numeric_limits<int64_t>::max();

        for (auto [pos, val] : dug_out)
        {
            max_x = std::max(max_x, pos.x);
            max_y = std::max(max_y, pos.y);

            min_x = std::min(min_x, pos.x);
            min_y = std::min(min_y, pos.y);
        }

        std::map<v2, int8_t> flood;

        for (int64_t y = min_y - 1; y <= max_y + 1; ++y)
        {
            for (int64_t x = min_x - 1; x <= max_x + 1; ++x)
            {
                v2 pos(x, y);
                if (dug_out.find(pos) == dug_out.end())
                    flood[pos] = 0;
                else
                    flood[pos] = 2;
            }
        }

        flood[v2(min_x - 1, min_y - 1)] = 1;
        auto neighbours = MapHelper::getNeighboursVec(false);

        std::queue<v2> marked;
        marked.push(v2(min_x - 1, min_y - 1));

        while (!marked.empty())
        {
            auto pos_orig = marked.front(); marked.pop();

            for (auto n : neighbours)
            {
                v2 pos = pos_orig + n;
                if (flood.find(pos) == flood.end())
                    continue;

                if (flood[pos] == 0)
                {
                    flood[pos] = 1;
                    marked.push(pos);
                }
            }
        }

        int32_t totalCount = 0;

        for (auto [pos, val] : flood)
        {
            if (val == 0 || val == 2)
                totalCount++;
        }

        return totalCount;
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

        int64_t totalCount = 0;

        for (int index = 0; index < polygon.size() - 1; ++index)
        {
            auto first = polygon[index];
            auto second = polygon[index + 1];

            totalCount += ((first.x + second.x) * (first.y - second.y));
        }

        totalCount = std::abs(totalCount);

        return totalCount / 2 + perimeter / 2 + 1;
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