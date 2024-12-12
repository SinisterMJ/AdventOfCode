#ifndef ADVENTOFCODE2024_DAY12
#define ADVENTOFCODE2024_DAY12

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day12 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    Map2DBase<int8_t> garden;

    std::set<v2> fullRegion(v2 start)
    {
        std::set<v2> region;
        region.insert(start);
        int8_t value = garden.read(start);

        bool foundNone = false;

        auto neighbours = MapHelper::getNeighboursVec(false);

        while (!foundNone)
        {
            foundNone = true;

            for (auto pos : region)
            {
                for (auto dir : neighbours)
                {
                    if (!garden.validIndex(dir + pos))
                        continue;

                    if (garden.read(dir + pos) == value && !region.contains(dir + pos))
                    {
                        region.insert(dir + pos);
                        foundNone = false;
                    }
                }
            }
        }

        return region;
    }

    int64_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
            for (int x = 0; x < inputVector[y].size(); ++x)
                garden.write(x, y, inputVector[y][x]);

        int64_t result = 0;
        std::set<v2> handled;
        auto neighbours = MapHelper::getNeighboursVec(false);

        for (int y = 0; y <= garden.maxY(); ++y)
        {
            for (int x = 0; x <= garden.maxX(); ++x)
            {
                if (handled.contains(v2(x, y)))
                    continue;

                int8_t val = garden.read(v2(x, y));
                // Find full set:
                auto region = fullRegion(v2(x, y));

                int64_t bounds = 0;
                for (auto pos : region)
                {
                    for (auto dir : neighbours)
                    {
                        if (!garden.validIndex(pos + dir))
                        {
                            bounds++;
                            continue;
                        }

                        if (garden.read(pos + dir) != val)
                            bounds++;
                    }
                }

                result += region.size() * bounds;
                handled.merge(region);
            }
        }

        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;
        std::set<v2> handled;
        auto neighbours = MapHelper::getNeighboursVec(false);

        for (int y = 0; y <= garden.maxY(); ++y)
        {
            for (int x = 0; x <= garden.maxX(); ++x)
            {
                if (handled.contains(v2(x, y)))
                    continue;

                int8_t value = garden.read(v2(x, y));
                // Find full set:
                auto region = fullRegion(v2(x, y));

                std::set<std::pair<v2, v2>> sides;

                int64_t bounds = 0;
                
                for (auto pos : region)
                {                   
                    for (auto dir : neighbours)
                    {
                        if (sides.contains(std::make_pair(pos, dir)))
                            continue;

                        v2 left(dir.y, -dir.x);
                        v2 right(-dir.y, dir.x);

                        if (!garden.validIndex(pos + dir))
                        {
                            sides.insert(std::make_pair(pos, dir));
                            bounds++;
                            v2 new_pos = pos;
                            for (;;)
                            {
                                if (garden.validIndex(new_pos + left) && garden.read(new_pos + left) == value)
                                {
                                    sides.insert(std::make_pair(new_pos + left, dir));
                                    new_pos = new_pos + left;
                                }
                                else 
                                    break;
                            }


                            new_pos = pos;
                            for (;;)
                            {
                                if (garden.validIndex(new_pos + right) && garden.read(new_pos + right) == value)
                                {
                                    sides.insert(std::make_pair(new_pos + right, dir));
                                    new_pos = new_pos + right;
                                }
                                else
                                    break;
                            }

                            continue;
                        }

                        if (garden.read(pos + dir) != value)
                        {
                            sides.insert(std::make_pair(pos, dir));
                            bounds++;

                            for (v2 new_pos = pos + left; garden.validIndex(new_pos) && garden.read(new_pos) == value; new_pos = new_pos + left)
                            {
                                if (garden.validIndex(new_pos + dir) && garden.read(new_pos + dir) != value)
                                    sides.insert(std::make_pair(new_pos, dir));
                                else
                                    break;
                            }

                            for (v2 new_pos = pos + right; garden.validIndex(new_pos) && garden.read(new_pos) == value; new_pos = new_pos + right)
                            {
                                if (garden.validIndex(new_pos + dir) && garden.read(new_pos + dir) != value)
                                    sides.insert(std::make_pair(new_pos, dir));
                                else
                                    break;
                            }

                            continue;
                        }
                    }
                }

                result += region.size() * bounds;
                handled.merge(region);
            }
        }

        return result;
    }

public:
    Day12()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_12.txt");
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

#endif  // ADVENTOFCODE2024_DAY12