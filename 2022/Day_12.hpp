#ifndef ADVENTOFCODE2022_DAY12
#define ADVENTOFCODE2022_DAY12

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <queue>

class Day12 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int solve(bool part_2)
    {
        std::map<v2, int8_t> jungle;
        v2 start(0, 0);

        std::set<v2> seen;

        std::queue<v2> currentPositions;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                jungle[start] = ch;

                if (part_2)
                {
                    if (ch == 'a')
                    {
                        currentPositions.push(start);
                        seen.insert(start);
                    }
                }
                else
                {
                    if (ch == 'S')
                    {
                        currentPositions.push(start);
                        seen.insert(start);
                    }
                }
                start.x++;
            }
            start.x = 0;
            start.y++;
        }


        int32_t steps = 0;
        auto neighbours = MapHelper::getNeighboursVec(false);

        while (true)
        {
            std::queue<v2> nextPositions;

            while (!currentPositions.empty())
            {
                auto pos = currentPositions.front();
                currentPositions.pop();

                if (jungle[pos] == 'E')
                    return steps;

                for (auto dir : neighbours)
                {
                    if (jungle[pos + dir] == 'E' && jungle[pos] != 'z')
                        continue;

                    if (jungle.contains(pos + dir) &&
                        seen.count(pos + dir) == 0 &&
                        ((jungle[pos + dir] - jungle[pos] <= 1)
                            || jungle[pos] == 'S'))
                    {
                        nextPositions.push(pos + dir);
                        seen.insert(pos + dir);
                    }
                }
            }

            steps++;
            currentPositions = nextPositions;
        }

        return steps;
    }

public:
    Day12()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_12.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_12.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY12