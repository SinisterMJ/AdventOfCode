#ifndef ADVENTOFCODE2024_DAY15
#define ADVENTOFCODE2024_DAY15

#include "../includes/aoc.h"
#include <algorithm>

class Day15 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::set<v2> walls;
        v2 robot;
        std::map<int32_t, v2> goods;
        std::vector<int8_t> instructions;

        int32_t id = 0;
        int y = 0;
        for (; inputVector[y] != ""; ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                if (inputVector[y][x] == '#')
                    walls.insert(v2(x, y));
                if (inputVector[y][x] == 'O')
                    goods[id++] = v2(x, y);
                if (inputVector[y][x] == '@')
                    robot = v2(x, y);
            }
        }

        for (y = y + 1; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                instructions.emplace_back(inputVector[y][x]);

        for (auto step : instructions)
        {
            v2 dir;
            if (step == '<')
                dir = v2(-1, 0);
            if (step == '>')
                dir = v2(1, 0);
            if (step == 'v')
                dir = v2(0, 1);
            if (step == '^')
                dir = v2(0, -1);

            if (walls.contains(robot + dir))
                continue;

            bool collision = false;

            for (auto [index, position] : goods)
            {
                if (position == robot + dir)
                    collision = true;
            }

            if (!collision)
                robot = robot + dir;
            else
            {
                v2 goods_pos = robot + dir;
                std::set<int32_t> found_goods;
                
                bool found_next = true;
                while (found_next)
                {
                    found_next = false;

                    for (auto [index, position] : goods)
                    {
                        if (position == goods_pos)
                        {
                            found_next = true;
                            found_goods.insert(index);
                            goods_pos += dir;
                            break;
                        }
                    }
                }

                // found all goods directly touching, now check if wall or free position
                // If wall, do absolutely nothing
                if (walls.contains(goods_pos))
                    continue;

                robot = robot + dir;

                for (auto index : found_goods)
                {
                    goods[index] += dir;
                }
            }            
        }

        int64_t total = 0;
        for (auto& [index, pos]: goods)
            total += pos.y * 100 + pos.x;

        return total;
    }

    int64_t part2()
    {
        std::set<v2> walls;
        v2 robot;
        std::map<int32_t, std::pair<v2, v2>> goods;
        std::vector<int8_t> instructions;

        int32_t id = 0;
        int y = 0;
        for (; inputVector[y] != ""; ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                if (inputVector[y][x] == '#')
                {
                    walls.insert(v2(2 * x, y));
                    walls.insert(v2(2 * x + 1, y));
                }
                if (inputVector[y][x] == 'O')
                {
                    goods[id++] = std::make_pair(v2(2 * x, y), v2(2 * x + 1, y));
                }
                if (inputVector[y][x] == '@')
                    robot = v2(2 * x, y);
            }
        }

        for (y = y + 1; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                instructions.emplace_back(inputVector[y][x]);

        for (auto step : instructions)
        {
            v2 dir;
            if (step == '<')
                dir = v2(-1, 0);
            if (step == '>')
                dir = v2(1, 0);
            if (step == 'v')
                dir = v2(0, 1);
            if (step == '^')
                dir = v2(0, -1);

            if (walls.contains(robot + dir))
                continue;

            bool collision = false;
            std::set<int32_t> found_goods;

            for (auto [index, position] : goods)
            {
                if (position.first == robot + dir || position.second == robot + dir)
                {
                    collision = true;
                    found_goods.insert(index);
                }
            }

            if (!collision)
                robot = robot + dir;
            else
            {   
                bool found_next = true;
                while (found_next)
                {
                    found_next = false;

                    for (auto& rob_index : found_goods)
                    {
                        for (auto [index, position] : goods)
                        {
                            if (index == rob_index)
                                continue;

                            if (found_goods.contains(index))
                                continue;

                            if (position.first == (goods[rob_index].first + dir)
                                or position.second == (goods[rob_index].first + dir)
                                or position.first == (goods[rob_index].second + dir))
                            {
                                found_next = true;
                                found_goods.insert(index);
                                break;
                            }
                        }
                    }
                }

                bool wall_hit = false;
                for (auto rob_index : found_goods)
                    if (walls.contains(goods[rob_index].first + dir) or walls.contains(goods[rob_index].second + dir))
                        wall_hit = true;

                // found all goods directly touching, now check if wall or free position
                // If wall, do absolutely nothing
                if (wall_hit)
                    continue;

                robot = robot + dir;

                for (auto index : found_goods)
                {
                    goods[index].first += dir;
                    goods[index].second += dir;
                }
            }
        }

        int64_t total = 0;
        for (auto& [index, pos] : goods)
            total += pos.first.y * 100 + pos.first.x;

        return total;
    }

public:
    Day15()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_15.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY15