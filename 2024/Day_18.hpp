#ifndef ADVENTOFCODE2024_DAY18
#define ADVENTOFCODE2024_DAY18

#include "../includes/aoc.h"
#include <algorithm>

class Day18 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        // initialize map
        std::map<v2, int8_t> card;

        for (int y = 0; y <= 70; ++y)
        {
            for (int x = 0; x <= 70; ++x)
            {
                card[v2(x, y)] = 0;
            }
        }

        for (int i = 0; i < 1024; ++i)
        {
            auto splits = util::splitInt(inputVector[i], ',');
            card[v2(splits[0], splits[1])] = 1;
        }

        std::set<v2> seen;
        auto neighbours = MapHelper::getNeighboursVec(false);
        std::queue<v2> positions;
        positions.push(v2(0, 0));
        seen.insert(v2(0, 0));

        int steps = 1;
        while (true)
        {
            std::queue<v2> new_positions;

            while (!positions.empty())
            {
                auto current = positions.front(); positions.pop();

                for (auto dir : neighbours)
                {
                    if (current + dir == v2(70, 70))
                        return steps;

                    if (!in_range<int64_t>((current + dir).x, 0, 70))
                        continue;

                    if (!in_range<int64_t>((current + dir).y, 0, 70))
                        continue;

                    if (seen.contains(current + dir))
                        continue;

                    if (card[current + dir] == 1)
                        continue;

                    seen.insert(current + dir);
                    new_positions.push(current + dir);
                }
            }

            steps++;
            std::swap(new_positions, positions);
        }


        return 0;
    }

    int64_t solve_map(int count_integers)
    {
        // initialize map
        std::map<v2, int8_t> card;

        for (int y = 0; y <= 70; ++y)
        {
            for (int x = 0; x <= 70; ++x)
            {
                card[v2(x, y)] = 0;
            }
        }

        for (int i = 0; i < count_integers; ++i)
        {
            auto splits = util::splitInt(inputVector[i], ',');
            card[v2(splits[0], splits[1])] = 1;
        }

        std::set<v2> seen;
        auto neighbours = MapHelper::getNeighboursVec(false);
        std::queue<v2> positions;
        positions.push(v2(0, 0));
        seen.insert(v2(0, 0));

        int steps = 1;
        while (true)
        {
            std::queue<v2> new_positions;

            while (!positions.empty())
            {
                auto current = positions.front(); positions.pop();

                for (auto dir : neighbours)
                {
                    if (current + dir == v2(70, 70))
                        return -1;

                    if (!in_range<int64_t>((current + dir).x, 0, 70))
                        continue;

                    if (!in_range<int64_t>((current + dir).y, 0, 70))
                        continue;

                    if (seen.contains(current + dir))
                        continue;

                    if (card[current + dir] == 1)
                        continue;

                    seen.insert(current + dir);
                    new_positions.push(current + dir);
                }
            }

            if (new_positions.empty())
                return count_integers;

            steps++;
            std::swap(new_positions, positions);
        }
    }

    std::string part2()
    {
        int max_i = static_cast<int32_t>(inputVector.size());
        int min_i = 1024;

        int test = (max_i + min_i) / 2;

        while (true)
        {
            if (solve_map(test) == -1)
            {
                min_i = test;
            }
            else
            {
                max_i = test;
            }

            if (min_i + 1 == max_i)
                // return min_i + 1;
                return inputVector[min_i];

            test = (max_i + min_i) / 2;
        }
    }

public:
    Day18()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_18.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_18.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 18 - Part 1: " << result_1 << '\n'
                  << "Day 18 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY18