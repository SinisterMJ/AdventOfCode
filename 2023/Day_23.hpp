#ifndef ADVENTOFCODE2023_DAY23
#define ADVENTOFCODE2023_DAY23

#include "../includes/aoc.h"
#include <algorithm>

class Day23 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    
    std::map<v2, int8_t> hike;
    std::vector<v2> neighbours = MapHelper::getNeighboursVec(false);

    int32_t getSteps(v2 current, v2 end, int32_t steps, std::set<v2> visited, bool part_one)
    {
        while (true)
        {
            std::vector<v2> possible;

            if (current == end)
                return steps;

            for (auto n : neighbours)
            {
                v2 position = current + n;

                if (visited.contains(position))
                    continue;

                if (!hike.contains(position) || hike[position] == '#')
                    continue;

                auto val = hike[position];

                if (part_one)
                {
                    if (val == '.')
                        possible.push_back(position);

                    if (val == '>' && n == v2(1, 0))
                        possible.push_back(position);

                    if (val == '<' && n == v2(-1, 0))
                        possible.push_back(position);

                    if (val == '^' && n == v2(0, -1))
                        possible.push_back(position);

                    if (val == 'v' && n == v2(0, 1))
                        possible.push_back(position);
                }
                else
                {
                    possible.push_back(position);
                }
            }

            if (possible.size() == 1)
            {
                current = possible[0];
                steps++;
                visited.insert(current);
            }

            int32_t maxSteps = 0;

            if (possible.size() > 1)
            {
                for (auto pos : possible)
                {
                    auto copiedVisited = visited;
                    copiedVisited.insert(pos);
                    maxSteps = std::max(maxSteps, getSteps(pos, end, steps + 1, copiedVisited, part_one));
                }

                return maxSteps;
            }
        }

        return -1;
    }

    std::pair<int32_t, int32_t> solve()
    {
        v2 start(0, 0);
        v2 current(0, 0);
        v2 exit(0, 0);
        
        bool foundStart = false;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                if (!foundStart && ch == '.')
                {
                    start = current;
                    foundStart = true;
                }

                if (ch == '.')
                    exit = current;
                
                hike[current] = ch;
                current.x++;
            }

            current.y++;
            current.x = 0;
        }

        std::set<v2> visited{ start };

        return std::make_pair(getSteps(start, exit, 0, visited, true), getSteps(start, exit, 0, visited, false));
    }

public:
    Day23()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_23.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_23.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
                  << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY23