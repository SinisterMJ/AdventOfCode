#ifndef ADVENTOFCODE2023_DAY17
#define ADVENTOFCODE2023_DAY17

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day17 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t solve(bool second_part)
    {
        std::map<v2, int8_t> heatmap;

        int x = 0;
        int y = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                heatmap[v2(x++, y)] = ch - '0';
            }

            y++;
            x = 0;
        }

        std::set<std::tuple<v2, v2, int8_t>> seen_states;
        
        std::priority_queue<std::tuple<int32_t, v2, v2, int8_t>, std::vector<std::tuple<int32_t, v2, v2, int8_t>>, std::greater<std::tuple<int32_t, v2, v2, int8_t>>> currents;
        currents.push(std::make_tuple(0, v2(0, 0), v2(0, 0), 5));

        v2 target(inputVector[0].size() - 1, y - 1);

        int32_t best = std::numeric_limits<int32_t>::max();
        auto neighbors = MapHelper::getNeighboursVec(false);

        v2 curr(0, 0);

        while (!currents.empty())
        {
            auto current = currents.top(); currents.pop();
            auto cost = std::get<0>(current);
            auto position = std::get<1>(current);
            auto direction = std::get<2>(current);
            auto duration = std::get<3>(current);

            if (position == target)
            {
                if (second_part && duration >= 4)
                {
                    return cost;
                }

                if (!second_part)
                    return cost;

                continue;
            }

            for (auto n : neighbors)
            {
                if (second_part)
                {
                    if (n != direction && duration < 4)
                        continue;

                    if (n == direction && duration == 10)
                        continue;
                }
                else
                {
                    if (n == direction && duration == 3)
                        continue;
                }

                auto new_position = position + n;
                if (heatmap.find(new_position) == heatmap.end())
                    continue;

                auto new_duration = 1;
                if (n == direction)
                    new_duration = duration + 1;

                if (n.x == -direction.x && n.y == -direction.y)
                    continue;

                auto new_cost = cost + heatmap[new_position];

                auto key = std::make_tuple(new_position, n, new_duration);
                if (seen_states.find(key) != seen_states.end())
                    continue;

                seen_states.insert(key);
                currents.push(std::make_tuple(new_cost, new_position, n, new_duration));
            }
        }

        return best;
    }

public:
    Day17()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_17.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 17 - Part 1: " << result_1 << '\n'
                  << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY17