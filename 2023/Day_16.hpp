#ifndef ADVENTOFCODE2023_DAY16
#define ADVENTOFCODE2023_DAY16

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day16 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int count_energized(v2 start, int direction)
    {
        std::map<v2, int8_t> mirrors;
        std::map<v2, int8_t> seen_rays;

        int x = 0;
        int y = 0;
        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                seen_rays[v2(x, y)] = 0;
                mirrors[v2(x++, y)] = ch;
            }

            y++;
            x = 0;
        }

        // 1 = east, 2 = south, 4 = west, 8 = north

        std::queue<std::pair<v2, int8_t>> rays;
        rays.push(std::make_pair(start, direction));

        while (!rays.empty())
        {
            auto [pos, dir] = rays.front(); rays.pop();
            v2 dir_v;
            if (dir == 1)
                dir_v = v2(1, 0);
            if (dir == 2)
                dir_v = v2(0, 1);
            if (dir == 4)
                dir_v = v2(-1, 0);
            if (dir == 8)
                dir_v = v2(0, -1);

            auto n_pos = pos + dir_v;
            if (seen_rays.find(n_pos) == seen_rays.end())
                continue;

            // This position has already seen this ray from this direction
            if (seen_rays[n_pos] & dir)
                continue;

            seen_rays[n_pos] += dir;
            if (mirrors[n_pos] == '.')
                rays.push(std::make_pair(n_pos, dir));


            if (mirrors[n_pos] == '-' && dir_v.y != 0)
            {
                rays.push(std::make_pair(n_pos, 1));
                rays.push(std::make_pair(n_pos, 4));
            }

            if (mirrors[n_pos] == '|' && dir_v.x != 0)
            {
                rays.push(std::make_pair(n_pos, 2));
                rays.push(std::make_pair(n_pos, 8));
            }


            if (mirrors[n_pos] == '|' && dir_v.x == 0)
                rays.push(std::make_pair(n_pos, dir));

            if (mirrors[n_pos] == '-' && dir_v.y == 0)
                rays.push(std::make_pair(n_pos, dir));


            if (mirrors[n_pos] == '/')
            {
                switch (dir) {
                case 1: rays.push(std::make_pair(n_pos, 8)); break;
                case 2: rays.push(std::make_pair(n_pos, 4)); break;
                case 4: rays.push(std::make_pair(n_pos, 2)); break;
                case 8: rays.push(std::make_pair(n_pos, 1)); break;
                default: break;
                }
            }

            if (mirrors[n_pos] == '\\')
            {
                switch (dir) {
                case 1: rays.push(std::make_pair(n_pos, 2)); break;
                case 2: rays.push(std::make_pair(n_pos, 1)); break;
                case 4: rays.push(std::make_pair(n_pos, 8)); break;
                case 8: rays.push(std::make_pair(n_pos, 4)); break;
                default: break;
                }
            }
        }

        int total = 0;

        for (auto [pos, val] : seen_rays)
            total += (val > 0);

        return total;
    }

    int64_t part1()
    {        
        return count_energized(v2(-1, 0), 1);
    }

    int64_t part2()
    {
        int maxVal = 0;
        for (int i = 0; i < inputVector.size(); ++i)
        {
            maxVal = std::max(count_energized(v2(-1, i), 1), maxVal);
            maxVal = std::max(count_energized(v2(inputVector[0].size(), i), 4), maxVal);
        }

        for (int i = 0; i < inputVector[0].size(); ++i)
        {
            maxVal = std::max(count_energized(v2(i, -1), 2), maxVal);
            maxVal = std::max(count_energized(v2(i, inputVector.size()), 8), maxVal);
        }

        return maxVal;
    }

public:
    Day16()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_16.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY16