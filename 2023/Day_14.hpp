#ifndef ADVENTOFCODE2023_DAY14
#define ADVENTOFCODE2023_DAY14

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day14 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    void moveRocks(std::map<v2, int8_t>& rocks, int direction)
    {
        // NORTH
        if (direction == 0)
        {
            for (int i = 0; i < inputVector.size(); ++i)
            {
                for (int j = 0; j < inputVector[0].size(); ++j)
                {
                    if (rocks[v2(j, i)] == 'O')
                    {
                        int y_new = i - 1;
                        while (y_new >= 0 && rocks[v2(j, y_new)] != '#' && rocks[v2(j, y_new)] != 'O')
                            y_new--;

                        if (y_new < 0 && rocks[v2(j, 0)] != '.')
                            continue;


                        y_new++;

                        rocks[v2(j, i)] = '.';
                        rocks[v2(j, y_new)] = 'O';
                    }
                }
            }
        }

        // WEST
        if (direction == 1)
        {
            for (int i = 0; i < inputVector.size(); ++i)
            {
                for (int j = 0; j < inputVector[0].size(); ++j)
                {
                    if (rocks[v2(j, i)] == 'O')
                    {
                        int x_new = j - 1;
                        while (x_new >= 0 && rocks[v2(x_new, i)] != '#' && rocks[v2(x_new, i)] != 'O')
                            x_new--;

                        if (x_new < 0 && rocks[v2(0, i)] != '.')
                            continue;


                        x_new++;

                        rocks[v2(j, i)] = '.';
                        rocks[v2(x_new, i)] = 'O';
                    }
                }
            }
        }

        // SOUTH
        if (direction == 2)
        {
            for (int i = (int)(inputVector.size()) - 1; i >= 0; --i)
            {
                for (int j = 0; j < inputVector[0].size(); ++j)
                {
                    if (rocks[v2(j, i)] == 'O')
                    {
                        int y_new = i + 1;
                        while (y_new < inputVector.size() && rocks[v2(j, y_new)] != '#' && rocks[v2(j, y_new)] != 'O')
                            y_new++;

                        if (y_new == inputVector.size() && rocks[v2(j, (int)(inputVector.size()) - 1)] != '.')
                            continue;

                        y_new--;

                        rocks[v2(j, i)] = '.';
                        rocks[v2(j, y_new)] = 'O';
                    }
                }
            }
        }

        // EAST
        if (direction == 3)
        {
            for (int i = 0; i < inputVector.size(); ++i)
            {
                for (int j = (int)(inputVector[0].size()) - 1; j >= 0; --j)
                {
                    if (rocks[v2(j, i)] == 'O')
                    {
                        int x_new = j + 1;
                        while (x_new < inputVector[0].size() && rocks[v2(x_new, i)] != '#' && rocks[v2(x_new, i)] != 'O')
                            x_new++;

                        if (x_new == inputVector[0].size() && rocks[v2((int)(inputVector[0].size()) - 1, i)] != '.')
                            continue;

                        x_new--;

                        rocks[v2(j, i)] = '.';
                        rocks[v2(x_new, i)] = 'O';
                    }
                }
            }
        }
    }

    int64_t part1()
    {
        std::map<v2, int8_t> rocks;

        int x = 0;
        int y = 0;
        for (auto line : inputVector)
        {
            for (auto ch : line)
                rocks[v2(x++, y)] = ch;

            x = 0;
            y++;
        }

        moveRocks(rocks, 0);

        int64_t result = 0;

        for (auto [pos, val] : rocks)
            if (val == 'O')
                result += y - pos.y;

        return result;
    }

    int64_t part2()
    {
        std::map<v2, int8_t> rocks;

        int x = 0;
        int y = 0;
        for (auto line : inputVector)
        {
            for (auto ch : line)
                rocks[v2(x++, y)] = ch;

            x = 0;
            y++;
        }

        std::map<std::map<v2, int8_t>, int64_t> seen;
        std::map<int64_t, int64_t> loads;

        // 4'000'000'000 because its 1'000'000'000 cycles, of each 4 movements
        for (int64_t index = 0; index < 4'000'000'000; ++index)
        {
            if (seen.find(rocks) != seen.end())
            {
                int64_t loop = index - seen[rocks];
                int64_t needed = (4'000'000'000 - seen[rocks]) / loop;
                int64_t offset = 4'000'000'000 - seen[rocks] - needed * loop;
                return loads[seen[rocks] + offset];
            }

            seen[rocks] = index;

            int64_t load = 0;
            for (auto [pos, val] : rocks)
                if (val == 'O')
                    load += inputVector.size() - pos.y;

            loads[index] = load;
            moveRocks(rocks, index % 4);
        }

        // If you reach this, grats on your RAM...
        return 0;
    }

public:
    Day14()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_14.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY14