#ifndef ADVENTOFCODE2023_DAY10
#define ADVENTOFCODE2023_DAY10

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <queue>

class Day10 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::set<int8_t> from_left{ '-', '7', 'J' };
    std::set<int8_t> from_right{ '-', 'L', 'F' };
    std::set<int8_t> from_top{ '|', 'L', 'J' };
    std::set<int8_t> from_bottom{ '|', '7', 'F' };
    Map2DBase<int8_t> plumbing;
    Map2DBase<int32_t> plumbing_distance;

    std::map<int8_t, std::pair<v2, v2>> directions;

    int64_t part1()
    {
        directions['-'] = std::make_pair(v2(-1, 0), v2(1, 0));
        directions['7'] = std::make_pair(v2(-1, 0), v2(0, 1));
        directions['J'] = std::make_pair(v2(-1, 0), v2(0, -1));
        directions['|'] = std::make_pair(v2(0, 1), v2(0, -1));
        directions['L'] = std::make_pair(v2(1, 0), v2(0, -1));
        directions['F'] = std::make_pair(v2(1, 0), v2(0, 1));

        int x = 0;
        int y = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                plumbing.write(v2(x, y), ch);
                plumbing_distance.write(v2(x, y), 0);
                ++x;
            }
            ++y; x = 0;
        }

        auto start = plumbing.find('S');
        
        if (
            from_left.find(plumbing.read(start + v2(1, 0))) != from_left.end() &&
            from_right.find(plumbing.read(start + v2(-1, 0))) != from_right.end()
            )
            plumbing.write(start, '-');
        
        if (
            from_left.find(plumbing.read(start + v2(1, 0))) != from_left.end() &&
            from_bottom.find(plumbing.read(start + v2(0, 1))) != from_bottom.end()
            )
            plumbing.write(start, 'F');
        
        if (
            from_left.find(plumbing.read(start + v2(1, 0))) != from_left.end() &&
            from_top.find(plumbing.read(start + v2(0, -1))) != from_top.end()
            )
            plumbing.write(start, 'L');

        if (
            from_right.find(plumbing.read(start + v2(-1, 0))) != from_right.end() &&
            from_top.find(plumbing.read(start + v2(0, 1))) != from_top.end()
            )
            plumbing.write(start, '7');

        if (
            from_right.find(plumbing.read(start + v2(-1, 0))) != from_right.end() &&
            from_bottom.find(plumbing.read(start + v2(0, -1))) != from_bottom.end()
            )
            plumbing.write(start, 'J');

        if (
            from_top.find(plumbing.read(start + v2(0, 1))) != from_top.end() &&
            from_bottom.find(plumbing.read(start + v2(0, -1))) != from_bottom.end()
            )
            plumbing.write(start, '|');

        auto neighbours = MapHelper::getNeighboursVec(false);

        std::queue<v2> curr;
        curr.push(start);

        while (!curr.empty())
        {
            auto pos = curr.front(); curr.pop();

            auto dirs = directions[plumbing.read(pos)];

            if (plumbing_distance.read(pos + dirs.first) == 0)
            {
                plumbing_distance.write(pos + dirs.first, plumbing_distance.read(pos) + 1);
                curr.push(pos + dirs.first);
            }
            
            if (plumbing_distance.read(pos + dirs.second) == 0)
            {
                plumbing_distance.write(pos + dirs.second, plumbing_distance.read(pos) + 1);
                curr.push(pos + dirs.second);
            }
        }

        int32_t max_val = 0;

        for (auto [pos, vals] : plumbing_distance.getMap())
        {
            max_val = std::max(max_val, vals);
        }

        return max_val;
    }

    int64_t part2()
    {
        directions['-'] = std::make_pair(v2(-1, 0), v2(1, 0));
        directions['7'] = std::make_pair(v2(-1, 0), v2(0, 1));
        directions['J'] = std::make_pair(v2(-1, 0), v2(0, -1));
        directions['|'] = std::make_pair(v2(0, 1), v2(0, -1));
        directions['L'] = std::make_pair(v2(1, 0), v2(0, -1));
        directions['F'] = std::make_pair(v2(1, 0), v2(0, 1));

        Map2DBase<int8_t> plumbing_2;

        int x = 0;
        int y = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                if (plumbing_distance.read(v2(x / 2, y / 2)) > 0)
                    plumbing_2.write(v2(x, y), '#');
                else
                    plumbing_2.write(v2(x, y), '0');
                
                plumbing_2.write(v2(x + 1, y), '0');
                plumbing_2.write(v2(x, y + 1), '0');
                plumbing_2.write(v2(x + 1, y + 1), '0');
                x += 2;
            }
            y += 2; x = 0;
        }
        auto neighbours = MapHelper::getNeighboursVec(false);

        for (int j = 0; j < inputVector.size() * 2; j += 2)
        {
            for (int i = 1; i < inputVector[0].size() * 2; i += 2)
            {
                v2 left(i - 1, j);
                v2 right(i + 1, j);

                if (plumbing_2.validIndex(left) && plumbing_2.validIndex(right))
                {
                    if (plumbing_2.read(left) == '#' && plumbing_2.read(right) == '#')
                    {
                        auto pipe_left = plumbing.read(left / 2);
                        auto pipe_right = plumbing.read(right / 2);
                        if (from_right.find(pipe_left) != from_right.end() && from_left.find(pipe_right) != from_left.end())
                            plumbing_2.write(v2(i, j), '#');
                    }
                }
            }
        }

        for (int j = 1; j < inputVector.size() * 2; j += 2)
        {
            for (int i = 0; i < inputVector[0].size() * 2; i += 2)
            {
                v2 down(i, j + 1);
                v2 up(i, j - 1);

                if (plumbing_2.validIndex(down) && plumbing_2.validIndex(up))
                {
                    if (plumbing_2.read(down) == '#' && plumbing_2.read(up) == '#')
                    {
                        auto pipe_up = plumbing.read(up / 2);
                        auto pipe_down = plumbing.read(down / 2);
                        if (from_bottom.find(pipe_up) != from_bottom.end() && from_top.find(pipe_down) != from_top.end())
                            plumbing_2.write(v2(i, j), '#');
                    }
                }
            }
        }

        auto pos_all = plumbing_distance.findAll(0);

        std::queue<v2> check;
        for (int i = 0; i < inputVector.size() * 2; i += 2)
        {
            check.push(v2(0, i));
            check.push(v2((int32_t)(inputVector[i / 2].size()) * 2 - 2, i));
        }

        for (int j = 2; j < inputVector.size() * 2; j += 2)
        {
            check.push(v2(j, 0));
            check.push(v2(j, (int32_t)(inputVector.size()) * 2 - 2));
        }

        while (!check.empty())
        {
            v2 curr = check.front(); check.pop();

            if (!plumbing_2.validIndex(curr))
                continue;

            if (plumbing_2.read(curr) == '0')
            {
                plumbing_2.write(curr, '1');
                for (auto n : neighbours)
                {
                    check.push(curr + n);
                }
            }
        }

        int total = 0;

        for (auto pos : pos_all)
            if (plumbing_2.read(pos * 2) != '1')
                total++;

        return total;
    }

public:
    Day10()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_10.txt");
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

#endif  // ADVENTOFCODE2023_DAY10