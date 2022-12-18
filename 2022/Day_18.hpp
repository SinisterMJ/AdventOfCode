#ifndef ADVENTOFCODE2022_DAY18
#define ADVENTOFCODE2022_DAY18

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day18 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::set<v3> cubes;
    int max_x, max_y, max_z, min_x, min_y, min_z;
    std::vector<v3> neighbours = MapHelper::getNeighboursVec3d(false);

    int64_t part1()
    {
        max_x = std::numeric_limits<int32_t>::min();
        max_y = std::numeric_limits<int32_t>::min();
        max_z = std::numeric_limits<int32_t>::min();

        min_x = std::numeric_limits<int32_t>::max();
        min_y = std::numeric_limits<int32_t>::max();
        min_z = std::numeric_limits<int32_t>::max();

        for (auto line : inputVector)
        {
            auto split = util::split(line, ',');
            v3 temp(std::stoi(split[0]), std::stoi(split[1]), std::stoi(split[2]));
            cubes.insert(temp);
            max_x = std::max(temp.x, max_x);
            max_y = std::max(temp.y, max_y);
            max_z = std::max(temp.z, max_z);

            min_x = std::min(temp.x, min_x);
            min_y = std::min(temp.y, min_y);
            min_z = std::min(temp.z, min_z);
        }

        int64_t exposed = 0;

        for (auto cube : cubes)
        {
            for (auto neigh : neighbours)
            {
                if (!cubes.contains(neigh + cube))
                    exposed++;
            }
        }

        return exposed;
    }

    bool outside(v3 position, std::set<v3>& checked)
    {
        bool is_outside = false;
        for (auto dir : neighbours)
        {
            if (cubes.contains(position + dir))
                continue;

            if (checked.contains(position + dir))
                continue;

            v3 res = position + dir;
            if (!in_range(res.x, min_x, max_x) ||
                !in_range(res.y, min_y, max_y) ||
                !in_range(res.z, min_z, max_z))
                return true;

            checked.insert(dir + position);
            is_outside |= outside(position + dir, checked);
            if (is_outside)
                return true;
        }

        return is_outside;
    }

    int64_t part2()
    {        
        int exposed_outside = 0;
        for (auto cube : cubes)
        {
            for (auto dir : neighbours)
            {
                std::set<v3> checked;
                if (!cubes.contains(dir + cube) &&
                    outside(dir + cube, checked))
                    exposed_outside++;
            }
        }

        return exposed_outside;
    }

public:
    Day18()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_18.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_18.txt");
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

#endif  // ADVENTOFCODE2022_DAY18