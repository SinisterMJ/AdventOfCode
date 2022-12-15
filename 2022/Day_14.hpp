#ifndef ADVENTOFCODE2022_DAY14
#define ADVENTOFCODE2022_DAY14

#include "../includes/aoc.h"
#include <unordered_set>

class Day14 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t solve(bool addFloor)
    {
        std::unordered_set<v2> occupied;
        int max_y = 0;
        for (auto line : inputVector)
        {
            auto paths = util::split(line, " -> ");
            v2 start(-1, -1);
            v2 last(-1, -1);
            for (auto point : paths)
            {
                auto coords = util::split(point, ',');
                start = v2(std::stoi(coords[0]), std::stoi(coords[1]));
                occupied.insert(start);
                if (last.x != -1 && last.y != -1)
                {
                    auto dir = (start - last).getDirection();
                    auto tempPos = last;
                    while (!(tempPos.x == start.x && tempPos.y == start.y))
                    {
                        occupied.insert(tempPos);
                        max_y = std::max(max_y, tempPos.y);
                        tempPos += dir;
                    }
                }
                last = start;
            }
        }

        max_y += 2;

        if (addFloor)
            for (int x = 500 - max_y - 2; x < 500 + max_y + 2; ++x)
                occupied.insert(v2(x, max_y));
        
        int sum = 0;
        bool settlement = true;
        while (settlement)
        {
            v2 spawn(500, 0);
            settlement = false;

            while (spawn.y < max_y)
            {
                // First down
                if (!occupied.contains(spawn + v2(0, 1)))
                {
                    spawn += v2(0, 1);
                    continue;
                }

                // Then check left
                if (!occupied.contains(spawn + v2(-1, 1)))
                {
                    spawn += v2(-1, 1);
                    continue;
                }

                // Then check right
                if (!occupied.contains(spawn + v2(1, 1)))
                {
                    spawn += v2(1, 1);
                    continue;
                }

                if (occupied.contains(spawn))
                    break;

                occupied.insert(spawn);
                settlement = true;      
                sum++;
                break;
            }
        }

        return sum;
    }

public:
    Day14()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_14.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_14.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY14