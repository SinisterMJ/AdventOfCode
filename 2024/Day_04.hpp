#ifndef ADVENTOFCODE2024_DAY04
#define ADVENTOFCODE2024_DAY04

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"


class Day04 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    Map2DBase<uint8_t> xmas_map;

    int64_t part1()
    {
        int result = 0;

        for (int y = 0; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                xmas_map.write(x, y, inputVector[y][x]);

        auto directions = MapHelper::getNeighboursVec(true);

        for (auto all_x : xmas_map.findAll('X'))
            for (auto direction : directions)
                result += (xmas_map.read(all_x + direction) == 'M') && (xmas_map.read(all_x + direction * 2) == 'A') && (xmas_map.read(all_x + direction * 3) == 'S');

        return result;
    }

    int64_t part2()
    {
        int result = 0;
        for (auto all_a : xmas_map.findAll('A'))
        {
            std::string left = "";
            left += xmas_map.read(all_a + v2(-1, -1));
            left += xmas_map.read(all_a + v2(1, 1));

            std::string right = "";
            right += xmas_map.read(all_a + v2(-1, 1));
            right += xmas_map.read(all_a + v2(1, -1));

            std::sort(left.begin(), left.end());
            std::sort(right.begin(), right.end());

            result += (left == "MS" && right == "MS");
        }

        return result;
    }

public:
    Day04()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_4.txt");
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

#endif  // ADVENTOFCODE2024_DAY04