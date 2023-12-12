#ifndef ADVENTOFCODE2023_DAY12
#define ADVENTOFCODE2023_DAY12

#include "../includes/aoc.h"
#include <algorithm>
#include <bitset>
#include <numeric>

class Day12 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<std::tuple<int32_t, int32_t, int32_t>, int64_t> seen;

    int64_t solve(std::string s, std::vector<int32_t>& blocks, int32_t position_dots, int32_t position_blocks, int32_t current_length)
    {
        auto key = std::make_tuple(position_dots, position_blocks, current_length);
        if (seen.find(key) != seen.end())
            return seen[key];

        if (position_dots == s.size())
        {
            if (position_blocks == blocks.size() && current_length == 0)
                return 1;
            else if (position_blocks == blocks.size() - 1 && blocks[position_blocks] == current_length)
                return 1;
            
            return 0;
        }

        int64_t total = 0;

        std::set<int8_t> chars{ '.', '#' };

        for (auto ch : chars)
        {
            if (s[position_dots] == ch || s[position_dots] == '?')
            {
                if (ch == '.' && current_length == 0)
                    total += solve(s, blocks, position_dots + 1, position_blocks, 0);
                else if (ch == '.' && current_length > 0 && position_blocks < blocks.size() && blocks[position_blocks] == current_length)
                    total += solve(s, blocks, position_dots + 1, position_blocks + 1, 0);
                else if (ch == '#')
                    total += solve(s, blocks, position_dots + 1, position_blocks, current_length + 1);
            }
        }

        seen[key] = total;
        return total;
    }

    int64_t count_possibilities_five(std::string input)
    {
        auto parts = util::split(input, ' ');
        parts[0] = parts[0] + "?" + parts[0] + "?" + parts[0] + "?" + parts[0] + "?" + parts[0];

        auto sets = util::splitInt(parts[1], ',');
        
        {
            std::vector<int32_t> temp;

            for (int i = 0; i < 5; ++i)
            {
                for (auto val : sets)
                    temp.push_back(val);
            }

            std::swap(temp, sets);
        }

        return solve(parts[0], sets, 0, 0, 0);
    }

    int64_t part1()
    {
        int64_t total = 0;

        for (auto line : inputVector)
        {
            seen.clear();
            auto parts = util::split(line, ' ');
            auto sets = util::splitInt(parts[1], ',');
            total += solve(parts[0], sets, 0, 0, 0);
        }
        return total;
    }

    int64_t part2()
    {
        int64_t total = 0;

        for (auto line : inputVector)
        {
            seen.clear();
            auto parts = util::split(line, ' ');
            parts[0] = parts[0] + "?" + parts[0] + "?" + parts[0] + "?" + parts[0] + "?" + parts[0];

            auto sets = util::splitInt(parts[1], ',');

            {
                std::vector<int32_t> temp;

                for (int i = 0; i < 5; ++i)
                {
                    for (auto val : sets)
                        temp.push_back(val);
                }

                std::swap(temp, sets);
            }
            total += solve(parts[0], sets, 0, 0, 0);
        }
        return total;
    }

public:
    Day12()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_12.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY12