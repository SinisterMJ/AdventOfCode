#ifndef ADVENTOFCODE2021_DAY15
#define ADVENTOFCODE2021_DAY15

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day15 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::unordered_map<v2, int32_t> risk_map;

    int64_t part1()
    {
        v2 curr_pos(0, 0);

        for (auto line : inputVec)
        {
            curr_pos.x = 0;
            for (auto ch : line)
            {
                int d = ch - '0';

                risk_map[curr_pos] = d;
                curr_pos.x++;
            }
            curr_pos.y++;
        }

        auto neighbours = MapHelper::getNeighboursVec(false);

        curr_pos = v2(0, 0);
        
        std::unordered_map<v2, int32_t> cummulative;
        cummulative[curr_pos] = 0;

        std::set<v2> new_positions;
        new_positions.insert(curr_pos);
        while (new_positions.size() != 0)
        {
            std::set<v2> added_positions;
            for (auto pos : new_positions)
            {
                auto val = cummulative[pos];
                for (auto n : neighbours)
                {
                    if (risk_map.find(n + pos) == risk_map.end())
                        continue;

                    if (cummulative.find(n + pos) == cummulative.end() && risk_map.find(n + pos) != risk_map.end())
                    {
                        cummulative[n + pos] = val + risk_map[n + pos];
                        added_positions.insert(n + pos);
                    }
                    else
                    {
                        if (val + risk_map[n + pos] < cummulative[n + pos])
                        {
                            cummulative[n + pos] = val + risk_map[n + pos];
                            added_positions.insert(n + pos);
                        }
                    }
                }
            }
            std::swap(added_positions, new_positions);
        }

        int max_x = 0;
        int max_y = 0;

        for (auto [pos, val] : cummulative)
        {
            max_x = std::max(pos.x, max_x);
            max_y = std::max(pos.y, max_y);
        }

        return cummulative[v2(max_x, max_y)];
    }

    int64_t part2()
    {
        v2 curr_pos(0, 0);

        for (auto line : inputVec)
        {
            curr_pos.x = 0;
            for (auto ch : line)
            {
                int d = ch - '0';

                risk_map[curr_pos] = d;
                curr_pos.x++;
            }
            curr_pos.y++;
        }

        int max_x = 0;
        int max_y = 0;

        for (auto [pos, val] : risk_map)
        {
            max_x = std::max(pos.x, max_x);
            max_y = std::max(pos.y, max_y);
        }

        max_x++;
        max_y++;

        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                if (y == 0 && x == 0)
                {
                    continue;
                }

                curr_pos.x = x * max_x;
                curr_pos.y = y * max_y;

                for (int inner_y = 0; inner_y < max_y; ++inner_y)
                {
                    curr_pos.x = x * max_x;
                    for (auto inner_x = 0; inner_x < max_x; ++inner_x)
                    {
                        risk_map[curr_pos] = risk_map[v2(inner_x, inner_y)] + x + y;
                        while (risk_map[curr_pos] > 9)
                        {
                            risk_map[curr_pos] -= 9;
                        }

                        curr_pos.x++;
                    }
                    curr_pos.y++;
                }
            }
        }

        auto neighbours = MapHelper::getNeighboursVec(false);

        curr_pos = v2(0, 0);

        std::unordered_map<v2, int32_t> cummulative;
        cummulative[curr_pos] = 0;

        std::set<v2> new_positions;
        new_positions.insert(curr_pos);
        while (new_positions.size() != 0)
        {
            std::set<v2> added_positions;
            for (auto pos : new_positions)
            {
                auto val = cummulative[pos];
                for (auto n : neighbours)
                {
                    if (risk_map.find(n + pos) == risk_map.end())
                        continue;

                    if (cummulative.find(n + pos) == cummulative.end() && risk_map.find(n + pos) != risk_map.end())
                    {
                        cummulative[n + pos] = val + risk_map[n + pos];
                        added_positions.insert(n + pos);
                    }
                    else
                    {
                        if (val + risk_map[n + pos] < cummulative[n + pos])
                        {
                            cummulative[n + pos] = val + risk_map[n + pos];
                            added_positions.insert(n + pos);
                        }
                    }
                }
            }
            std::swap(added_positions, new_positions);
        }

        max_x = 0;
        max_y = 0;

        for (auto [pos, val] : cummulative)
        {
            max_x = std::max(pos.x, max_x);
            max_y = std::max(pos.y, max_y);
        }

        return cummulative[v2(max_x, max_y)];
    }

public:
    Day15()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_15.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_15.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 15 - Part 1: " << result_1 << '\n'
            << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
