#ifndef ADVENTOFCODE2023_DAY21
#define ADVENTOFCODE2023_DAY21

#include "../includes/aoc.h"
#include <algorithm>

class Day21 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::map<v2, int8_t> map;
        v2 current(0, 0);
        v2 start;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                if (ch == 'S')
                    start = current;

                map[current] = ch;
                current.x++;
            }
            current.x = 0;
            current.y++;
        }

        std::set<v2> positions;
        positions.insert(start);
        auto neighbours = MapHelper::getNeighboursVec(false);

        for (int index = 0; index < 64; ++index)
        {
            std::set<v2> new_positions;

            for (auto pos : positions)
                for (auto n : neighbours)
                    if (map.find(pos + n) != map.end() && map[pos + n] != '#')
                        new_positions.insert(pos + n);
                
            std::swap(new_positions, positions);
        }

        return positions.size();
    }

    int64_t part2()
    {
        std::unordered_map<v2, int8_t> map;
        v2 current(0, 0);
        v2 start;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                if (ch == 'S')
                    start = current;
                 
                // Make 5 copies of it in each direction
                map[current] = ch;

                for (int i = -5; i <= 5; ++i)
                    for (int j = -5; j <= 5; ++j)
                        map[v2(current.x + inputVector[0].size() * i, current.y + inputVector.size() * j)] = ch;

                current.x++;
            }
            current.x = 0;
            current.y++;
        }

        std::set<v2> positions;
        positions.insert(start);
        auto neighbours = MapHelper::getNeighboursVec(false);

        int64_t a0 = 0;
        int64_t a1 = 0;
        int64_t a2 = 0;

        for (int index = 1; index <= 65 + 2 * 131; ++index)
        {
            std::set<v2> new_positions;

            for (auto pos : positions)
                for (auto n : neighbours)
                    if (map[pos + n] != '#')
                        new_positions.insert(pos + n);

            std::swap(new_positions, positions);

            if (index == 65)
                a0 = positions.size();
            if (index == (65 + 1 * 131))
                a1 = positions.size();
            if (index == (65 + 2 * 131))
                a2 = positions.size();
        }

        int64_t first_difference01 = a1 - a0;
        int64_t first_difference12 = a2 - a1;
        int64_t second_difference = first_difference12 - first_difference01;

        int64_t A = second_difference / 2;
        int64_t C = a0;
        int64_t B = a1 - A - C;
        int64_t n = 26501365 / 131;
        return A * n * n + B * n + C;
    }

public:
    Day21()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_21.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_21.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY21