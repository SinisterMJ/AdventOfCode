#ifndef ADVENTOFCODE2024_DAY08
#define ADVENTOFCODE2024_DAY08

#include "../includes/aoc.h"
#include <algorithm>

class Day08 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::map<v2, int8_t> base;
    std::set<int8_t> towers;
    int64_t x_max = 0;
    int64_t y_max = 0;

    int64_t part1()
    {
        std::map<v2, int8_t> targets;

        int64_t x_s = 0;
        int64_t y_s = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                x_max = std::max(x_max, x_s);
                base[v2(x_s++, y_s)] = ch;
                if (ch != '.')
                    towers.insert(ch);
            }
            x_s = 0;
            y_max = y_s;
            y_s++;
        }

        for (auto c : towers)
        {
            std::vector<v2> positions;
            for (auto [pos, el] : base)
                if (el == c)
                    positions.push_back(pos);

            for (int i = 0; i < positions.size(); ++i)
            {
                for (int j = i + 1; j < positions.size(); ++j)
                {
                    v2 conn = positions[i] - positions[j];
                    v2 left = positions[i] + conn;
                    v2 right = positions[j] - conn;

                    if (in_range<int64_t>(left.y, 0, y_max) && in_range<int64_t>(left.x, 0, x_max))
                        targets[left] = 1;
                    if (in_range<int64_t>(right.y, 0, y_max) && in_range<int64_t>(right.x, 0, x_max))
                        targets[right] = 1;
                }
            }
        }

        return targets.size();
    }

    int64_t part2()
    {
        std::map<v2, int8_t> targets;


        for (auto c : towers)
        {
            std::vector<v2> positions;
            for (auto [pos, el] : base)
                if (el == c)
                    positions.push_back(pos);

            for (int i = 0; i < positions.size(); ++i)
            {
                for (int j = i + 1; j < positions.size(); ++j)
                {
                    v2 conn = positions[i] - positions[j];
                    for (int r = -50; r <= 50; ++r)
                    {
                        v2 t = positions[i] + conn * r;
                        if (in_range<int64_t>(t.y, 0, y_max) && in_range<int64_t>(t.x, 0, x_max))
                            targets[t] = 1;
                    }
                }
            }
        }

        return targets.size();
    }

public:
    Day08()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY08