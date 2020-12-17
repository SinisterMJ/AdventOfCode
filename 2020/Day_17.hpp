#ifndef ADVENTOFCODE2020_DAY17
#define ADVENTOFCODE2020_DAY17

#include "../includes/aoc.h"
#include <map>

class Day17 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    
    int64_t conway_cubes(bool cycle_w)
    {
        int32_t max_x = static_cast<int32_t>(inputVec[0].size() - 1);
        int32_t min_x = 0;
        int32_t max_y = static_cast<int32_t>(inputVec.size() - 1);
        int32_t min_y = 0;
        int32_t max_z = 0;
        int32_t max_w = 0;

        std::map<v4, bool> space;
        std::map<v4, bool> space_next;
        std::vector<v4> neighbours;

        for (int y = 0; y < inputVec.size(); ++y)
        {
            for (int x = 0; x < inputVec[0].size(); ++x)
            {
                v4 pos4(x, y, 0, 0);
                space[pos4] = (inputVec[y][x] == '#');
            }
        }

        for (int z = -1; z <= 1; z++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int w = -(cycle_w * 1); w <= (cycle_w * 1); w++)
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
            for (int z = 0; z <= max_z + 1; z++)
            {
                for (int y = min_y - 1; y <= max_y + 1; y++)
                {
                    for (int x = min_x - 1; x <= max_x + 1; x++)
                    {
                        for (int w = 0; w <= max_w + cycle_w; w++)
                        {
                            v4 pos(x, y, z, w);
                            int32_t activeNeighbours = 0;

                            for (auto elem : neighbours)
                            {
                                v4 neigh = pos + elem;
                                neigh.w = std::abs(neigh.w);
                                neigh.z = std::abs(neigh.z);
                                activeNeighbours += space[neigh];
                            }

                            space_next[pos] = space[pos] ? in_range(activeNeighbours, 2, 3) : activeNeighbours == 3;
                        }
                    }
                }
            }

            max_x++;
            max_y++;
            min_x--;
            min_y--;

            max_z++;

            if (cycle_w)
                max_w++;

            std::swap(space, space_next);
        }

        int64_t active = 0;
                
        for (auto elem : space)
        {
            int32_t val = elem.second;

            if (elem.first.z > 0)
                val *= 2;
            if (elem.first.w > 0)
                val *= 2;

            active += val;
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
        
        int64_t result_1 = conway_cubes(false);
        int64_t result_2 = conway_cubes(true);

        int64_t time = myTime.usPassed();
        std::cout << "Day 17 - Part 1: " << result_1 << '\n'
                  << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY17
