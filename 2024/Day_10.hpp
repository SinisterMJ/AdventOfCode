#ifndef ADVENTOFCODE2024_DAY10
#define ADVENTOFCODE2024_DAY10

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day10 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::vector<v2> neighbours;
    Map2DBase<int8_t> heights;

    int64_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                heights.write(x, y, inputVector[y][x] - '0');
                
        
        neighbours = MapHelper::getNeighboursVec(false);
        int64_t total = 0;
        for (auto start : heights.findAll(0))
        {
            std::set<v2> n;
            std::set<v2> heads;
            n.insert(start);

            for (int i = 1; i <= 9; ++i)
            {
                std::set<v2> new_pos;
                for (auto pos : n)
                {
                    for (auto dir : neighbours)
                    {
                        if (heights.validIndex(pos + dir) && heights.read(pos + dir) == i)
                        {
                            new_pos.insert(pos + dir);
                            if (i == 9)
                                heads.insert(pos + dir);
                        }
                    }
                }
                std::swap(n, new_pos);
            }

            total += heads.size();
        }

        return total;
    }

    int32_t paths(v2 curr, int target)
    {
        if (heights.validIndex(curr) && heights.read(curr) == 9)
            return 1;

        int32_t total = 0;
        for (auto dir : neighbours)
            if (heights.validIndex(curr + dir) && heights.read(curr + dir) == target)
                total += paths(curr + dir, target + 1);

        return total;
    }

    int64_t part2()
    {
        int total = 0;
        for (auto start : heights.findAll(0))
            total += paths(start, 1);

        return total;
    }

public:
    Day10()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_10.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY10