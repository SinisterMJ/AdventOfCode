#ifndef ADVENTOFCODE2025_DAY07
#define ADVENTOFCODE2025_DAY07

#include "../includes/aoc.h"
#include <algorithm>

class Day07 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::map<v2, int64_t> costs;

    int64_t part1()
    {
        std::vector<bool> rays(inputVector[0].size(), false);
        std::set<v2> activated;

        int y = 0;
        for (const auto& line : inputVector)
        {
            if (line.find('S') != std::string::npos)
            {
                int x = static_cast<int32_t>(line.find('S'));
                rays[x] = true;
            };

            for (int x = 0; x < line.size(); x++)
            {
                if (line[x] == '^' && rays[x])
                {
                    rays[x] = false;
                    rays[x - 1] = true;
                    rays[x + 1] = true;
                    activated.insert(v2(x, y));
                }
            }

            y++;
        }

        return activated.size();
    }

    int64_t paths(v2 pos)
    {
        if (costs.contains(pos))
            return costs[pos];

        if (pos.y == inputVector.size())
            return 1;

        if (inputVector[pos.y][pos.x] == '^')
        {
            auto cost = paths(pos + v2(1, 1)) + paths(pos + v2(-1, 1));
            costs[pos] = cost;
            return cost;
        }

        return paths(pos + v2(0, 1));
    }

    int64_t part2()
    {
        v2 start(inputVector[0].find('S'), 0);
        return paths(start);
    }

public:
    Day07()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY07