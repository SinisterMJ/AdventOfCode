#ifndef ADVENTOFCODE2024_DAY16
#define ADVENTOFCODE2024_DAY16

#include "../includes/aoc.h"
#include <algorithm>
#include <queue>
#include "../includes/Map2DBase.h"

class Day16 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    Map2DBase<int8_t> map;
    v2 start;
    v2 end;

    int32_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                map.write(x, y, inputVector[y][x]);

                if (inputVector[y][x] == 'E')
                {
                    end = v2(x, y);
                    map.write(x, y, '.');
                }
                if (inputVector[y][x] == 'S')
                {
                    start = v2(x, y);
                    map.write(x, y, '.');
                }
            }
        }

        std::map<std::pair<v2, v2>, int32_t> cost_map;
        
        cost_map[std::make_pair(start, v2(1, 0))] = 0;
        
        std::priority_queue<std::tuple<int32_t, v2, v2>, std::vector<std::tuple<int32_t, v2, v2>>, std::greater<std::tuple<int32_t, v2, v2>>> spots;
        spots.push(std::make_tuple(0, start, v2(1, 0)));

        while (!spots.empty())
        {
            auto state = spots.top(); spots.pop();
            auto cost = std::get<0>(state);
            auto position = std::get<1>(state);
            auto direction = std::get<2>(state);

            if (position == end)
                return cost;

            if (cost_map.find(std::make_pair(position, direction)) != cost_map.end() && cost_map[std::make_pair(position, direction)] < cost)
                continue;

            cost_map[std::make_pair(position, direction)] = cost;

            auto left = v2(-direction.y, direction.x);
            if (map.read(position + left) == '.')
                spots.push(std::make_tuple(cost + 1000, position, left));

            auto right = v2(direction.y, -direction.x);
            if (map.read(position + right) == '.')
                spots.push(std::make_tuple(cost + 1000, position, right));

            if (map.read(position + direction) == '.')
                spots.push(std::make_tuple(cost + 1, position + direction, direction));

        }
        return 0;
    }

    int32_t part2(int32_t max_cost)
    {
        std::map<std::pair<v2, v2>, int32_t> cost_map;

        cost_map[std::make_pair(start, v2(1, 0))] = 0;

        std::priority_queue<std::tuple<int32_t, v2, v2, std::set<v2>>, std::vector<std::tuple<int32_t, v2, v2, std::set<v2>>>, std::greater<std::tuple<int32_t, v2, v2, std::set<v2>>>> paths;
        paths.push(std::make_tuple(0, start, v2(1, 0), std::set<v2>()));

        std::set<v2> passed_points;
        passed_points.insert(start);

        while (!paths.empty())
        {
            auto state = paths.top(); paths.pop();
            auto cost = std::get<0>(state);
            auto position = std::get<1>(state);
            auto direction = std::get<2>(state);
            auto visited = std::get<3>(state);

            if (cost > max_cost)
                continue;

            if (position == end && cost == max_cost)
                passed_points.merge(visited);

            if (cost_map.find(std::make_pair(position, direction)) != cost_map.end() && cost_map[std::make_pair(position, direction)] < cost)
                continue;

            cost_map[std::make_pair(position, direction)] = cost;

            auto left = v2(-direction.y, direction.x);
            if (map.read(position + left) == '.')
                paths.push(std::make_tuple(cost + 1000, position, left, visited));

            auto right = v2(direction.y, -direction.x);
            if (map.read(position + right) == '.')
                paths.push(std::make_tuple(cost + 1000, position, right, visited));

            if (map.read(position + direction) == '.')
            {
                std::set<v2> copyVisited = visited;
                copyVisited.insert(position + direction);
                paths.push(std::make_tuple(cost + 1, position + direction, direction, copyVisited));
            }
        }

        return passed_points.size();
    }

public:
    Day16()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_16.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2(result_1);

        int64_t time = myTime.usPassed();

        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY16