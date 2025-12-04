#ifndef ADVENTOFCODE2025_DAY04
#define ADVENTOFCODE2025_DAY04

#include "../includes/aoc.h"
#include <algorithm>
#include <unordered_map>

class Day04 {
private:

    std::vector<std::string> inputVector;

    int64_t run(bool part_2)
    {
        std::unordered_map<v2, bool> grid;
        for (int y = 0; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                if (inputVector[y][x] == '@')
                    grid[v2(x, y)] = true;

        int count = 0;
        const auto& neighbors = MapHelper::getNeighboursVec(true);
        bool removed = true;
        while (removed)
        {
            removed = false;
            for (auto& elem : grid)
            {
                int c = 0;
                for (const auto& n : neighbors)
                {
                    v2 nPos = elem.first + n;
                    if (grid.find(nPos) != grid.end())
                        c++;
                }

                count += c < 4;
                if (c < 4 && part_2)
                {
                    grid.erase(elem.first);
                    removed = true;
                }
            }
        }
        return count;
    }

public:
    Day04()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_4.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = run(false);
        auto result_2 = run(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY04