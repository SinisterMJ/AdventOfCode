#ifndef ADVENTOFCODE2021_DAY15
#define ADVENTOFCODE2021_DAY15

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day15 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::unordered_map<v2, int32_t> risk_map;

    int64_t max_x{ 0 };
    int64_t max_y{ 0 };

    void buildmap(bool big)
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

        max_x = curr_pos.x;
        max_y = curr_pos.y;

        if (!big)
            return;

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

        max_x = curr_pos.x;
        max_y = curr_pos.y;
    }

    int64_t solve()
    {
        auto neighbours = MapHelper::getNeighboursVec(false);
        max_x--; max_y--;

        std::set<v2> seen;
        std::set<std::pair<int32_t, v2>> candidates;
        candidates.insert(std::make_pair(0, v2(0, 0)));
        seen.insert(v2(0, 0));

        while (candidates.size() > 0)
        {
            auto vec = *candidates.begin();
            candidates.erase(vec);

            for (auto& n : neighbours)
            {
                auto pos = n + vec.second;

                if (in_range<int64_t>(pos.x, 0, max_x) && in_range<int64_t>(pos.y, 0, max_y))
                {
                    if (seen.find(pos) != seen.end())
                        continue;

                    seen.insert(pos);
                    int value = vec.first + risk_map[pos];
                    candidates.insert(std::make_pair(value, pos));

                    if (pos.x == max_x && pos.y == max_y)
                        return value;
                }
            }
        }

        return 0;
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

        buildmap(false);
        auto result_1 = solve();

        buildmap(true);
        auto result_2 = solve();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 15 - Part 1: " << result_1 << '\n'
            << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
