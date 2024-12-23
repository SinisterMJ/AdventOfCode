#ifndef ADVENTOFCODE2024_DAY20
#define ADVENTOFCODE2024_DAY20

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day20 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    Map2DBase<int8_t> race;

    std::map<v2, int32_t> steps_to_end;
    v2 start;
    v2 end;

    int64_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                race.write(x, y, inputVector[y][x]);

        start = race.find('S');
        end = race.find('E');

        std::queue<v2> reached;
        reached.push(end);

        auto neighbours = MapHelper::getNeighboursVec(false);

        int32_t steps = 0;
        steps_to_end[end] = 0;

        for (;;)
        {
            steps++;
            std::queue<v2> new_reached;
            while (!reached.empty())
            {
                v2 pos = reached.front(); reached.pop();

                for (auto& dir : neighbours)
                {
                    if (race.read(pos + dir) == '#')
                        continue;

                    if (steps_to_end.count(pos + dir) != 0)
                        continue;

                    steps_to_end[pos + dir] = steps;
                    new_reached.push(pos + dir);
                }
            }

            if (new_reached.empty())
                break;

            std::swap(new_reached, reached);
        }

        v2 pos = start;
        int result = 0;
        
        while (pos != end)
        {
            for (auto& dir : neighbours)
            {
                if (steps_to_end.count(pos + dir * 2) == 0)
                    continue;

                result += ((steps_to_end[pos] - steps_to_end[pos + dir * 2] - 2) >= 100);
            }

            for (auto& dir : neighbours)
            {
                if (steps_to_end.count(pos + dir) == 0)
                    continue;

                if (steps_to_end[pos] > steps_to_end[pos + dir])
                {
                    pos = pos + dir;
                    break;
                }
            }
        }

        return result;
    }

    int64_t part2()
    {
        v2 pos = start;
        int result = 0;
        auto neighbours = MapHelper::getNeighboursVec(false);

        while (pos != end)
        {
            for (int dy = -20; dy <= 20; ++dy)
            {
                for (int dx = -20; dx <= 20; ++dx)
                {
                    v2 dir(dx, dy);
                    if (dir.manhattan() > 20)
                        continue;

                    if (steps_to_end.count(pos + dir) == 0)
                        continue;

                    result += ((steps_to_end[pos] - steps_to_end[pos + dir] - dir.manhattan()) >= 100);
                }
            }

            for (auto& dir : neighbours)
            {
                if (steps_to_end.count(pos + dir) == 0)
                    continue;

                if (steps_to_end[pos] > steps_to_end[pos + dir])
                {
                    pos = pos + dir;
                    break;
                }
            }
        }

        return result;
    }

public:
    Day20()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_20.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_20.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 20 - Part 1: " << result_1 << '\n'
                  << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY20