#ifndef ADVENTOFCODE2020_DAY17
#define ADVENTOFCODE2020_DAY17

#include "../includes/aoc.h"
#include <map>

class Day17 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::map<v3, bool> space;
    std::map<v4, bool> space4;
    int32_t max_x;
    int32_t min_x;
    int32_t max_y;
    int32_t min_y;
    int32_t max_z;
    int32_t max_w;

    int64_t part1() 
    {
        std::map<v3, bool> space_next;
        std::vector<v3> neighbours;

        for (int z = -1; z <= 1; z++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    if (x == 0 && y == 0 && z == 0)
                        continue;

                    neighbours.push_back(v3(x, y, z));
                }
            }
        }

        for (int cycle = 0; cycle < 6; ++cycle)
        {
            for (int z = -max_z - 1; z <= max_z + 1; z++)
            {
                for (int y = min_y - 1; y <= max_y + 1; y++)
                {
                    for (int x = min_x - 1; x <= max_x + 1; x++)
                    {
                        v3 pos(x, y, z);
                        bool value = space[pos];

                        int32_t activeNeighbours = 0;
                        for (auto elem : neighbours)
                        {
                            v3 neigh = pos + elem;
                            activeNeighbours += space[neigh];
                        }

                        if (value)
                        {
                            if (!in_range(activeNeighbours, 2, 3))
                            {
                                space_next[pos] = false;
                            }
                            else
                            {
                                space_next[pos] = true;
                            }
                        }
                        else
                        {
                            if (activeNeighbours == 3)
                            {
                                space_next[pos] = true;
                            }
                            else
                            {
                                space_next[pos] = false;
                            }
                        }
                    }
                }
            }

            max_x++;
            max_y++;
            max_z++;
            min_x--;
            min_y--;

            std::swap(space, space_next);                       
        }

        int32_t active = 0;
        for (auto elem : space)
        {
            active += elem.second;
        }

        return active;
    }

    int64_t part2()
    {
        std::map<v4, bool> space_next;
        std::vector<v4> neighbours;

        for (int z = -1; z <= 1; z++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int w = -1; w <= 1; w++)
                    {
                        if (x == 0 && y == 0 && z == 0 && w == 0)
                            continue;

                        neighbours.push_back(v4(x, y, z, w));
                    }
                }
            }
        }

        for (int cycle = 0; cycle < 6; ++cycle)
        {
            for (int z = -max_z - 1; z <= max_z + 1; z++)
            {
                for (int y = min_y - 1; y <= max_y + 1; y++)
                {
                    for (int x = min_x - 1; x <= max_x + 1; x++)
                    {
                        for (int w = -max_w - 1; w <= max_w + 1; w++)
                        {
                            v4 pos(x, y, z, w);
                            bool value = space4[pos];

                            int32_t activeNeighbours = 0;

                            for (auto elem : neighbours)
                            {
                                v4 neigh = pos + elem;
                                activeNeighbours += space4[neigh];
                            }

                            if (value)
                            {
                                if (!in_range(activeNeighbours, 2, 3))
                                {
                                    space_next[pos] = false;
                                }
                                else
                                {
                                    space_next[pos] = true;
                                }
                            }
                            else
                            {
                                if (activeNeighbours == 3)
                                {
                                    space_next[pos] = true;
                                }
                                else
                                {
                                    space_next[pos] = false;
                                }
                            }
                        }
                    }
                }
            }

            max_x++;
            max_y++;
            max_z++;
            max_w++;

            min_x--;
            min_y--;

            std::swap(space4, space_next);
        }

        int32_t active = 0;
        for (auto elem : space4)
        {
            active += elem.second;
        }

        return active;
    }

public:
    Day17()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_17.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_17.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        min_y = min_x = 0;
        max_y = inputVec.size() - 1;
        max_x = inputVec[0].size() - 1;
        max_z = 0;
        max_w = 0;

        for (int y = 0; y < inputVec.size(); ++y)
        {
            for (int x = 0; x < inputVec[0].size(); ++x)
            {
                v3 pos(x, y, 0);
                v4 pos4(x, y, 0, 0);
                space[pos] = (inputVec[y][x] == '#');
                space4[pos4] = (inputVec[y][x] == '#');
            }
        }

        int64_t result_1 = part1();

        min_y = min_x = 0;
        max_y = inputVec.size() - 1;
        max_x = inputVec[0].size() - 1;
        max_z = 0;
        max_w = 0;

        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 17 - Part 1: " << result_1 << '\n'
                  << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY17
