#ifndef ADVENTOFCODE2023_DAY22
#define ADVENTOFCODE2023_DAY22

#include "../includes/aoc.h"
#include <algorithm>
#include <ranges>

class Day22 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Brick {
        v3 start;
        v3 end;
    };

    std::vector<Brick> allBricks;
    std::map<v3, int32_t> resting;
    std::map<int32_t, std::vector<v3>> blocks_resting;

    std::vector<v3> getAllBlocks(Brick input)
    {
        std::set<v3> result;

        auto direction = (input.end - input.start).normalize();

        v3 current = input.start;

        do {
            result.insert(current);
            current += direction;
        } while (current != input.end);
        
        result.insert(input.end);

        return std::vector<v3>(result.begin(), result.end());
    }

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            auto parts = util::split(line, '~');
            auto dimensions = util::splitInt(parts[0], ',');
            Brick temp;
            temp.start = v3(dimensions[0], dimensions[1], dimensions[2]);
            
            dimensions = util::splitInt(parts[1], ',');
            temp.end = v3(dimensions[0], dimensions[1], dimensions[2]);

            allBricks.push_back(temp);
        }

        std::ranges::sort(allBricks, [](const Brick& a, const Brick& b)
            {
                return a.start.z < b.start.z;
            }
        );

        for (int index = 1; index <= allBricks.size(); ++index)
        {
            auto b = allBricks[index - 1];
            auto blocks = getAllBlocks(b);
            bool stabilized = false;

            while (!stabilized)
            {
                for (const auto& block : blocks)
                    if (block.z - 1 == 0 || resting.find(v3(block.x, block.y, block.z - 1)) != resting.end())
                            stabilized = true;
                
                if (!stabilized)
                    for (auto& block : blocks)
                        block.z--;
            }

            for (const auto& block : blocks)
            {
                resting[block] = index;
                blocks_resting[index].push_back(block);
            }
        }

        int32_t removable = 0;

        for (int index = 1; index <= allBricks.size(); ++index)
        {
            std::set<int32_t> candidates;

            for (auto& block : blocks_resting[index])
            {
                if (resting.find(v3(block.x, block.y, block.z + 1)) != resting.end() && resting[v3(block.x, block.y, block.z + 1)] != index)
                    candidates.insert(resting[v3(block.x, block.y, block.z + 1)]);
            }

            bool relied = true;

            for (auto i : candidates)
            {
                std::set<int32_t> restingOn;

                for (const auto& block : blocks_resting[i])
                {
                    if (resting.find(v3(block.x, block.y, block.z - 1)) != resting.end() && resting[v3(block.x, block.y, block.z - 1)] != i)
                        restingOn.insert(resting[v3(block.x, block.y, block.z - 1)]);
                }

                relied &= (restingOn.size() > 1);
            }

            removable += relied;
        }

        return removable;
    }

    int64_t part2()
    {
        int64_t falling = 0;

        std::map<int32_t, std::set<int32_t>> dependencies;
        std::map<int32_t, std::set<int32_t>> r_dependencies;

        for (int index = 1; index <= allBricks.size(); ++index)
        {
            for (auto& block : blocks_resting[index])
            {
                if (resting.find(v3(block.x, block.y, block.z + 1)) != resting.end() && resting[v3(block.x, block.y, block.z + 1)] != index)
                {
                    dependencies[index].insert(resting[v3(block.x, block.y, block.z + 1)]);
                    r_dependencies[resting[v3(block.x, block.y, block.z + 1)]].insert(index);
                }
            }
        }

        
        for (int index = 1; index <= allBricks.size(); ++index)
        {
            std::set<int32_t> fallen{ index };
            
            bool chained = true;

            while (chained)
            {
                chained = false;

                for (int i = 1; i <= allBricks.size(); ++i)
                {
                    if (fallen.find(i) == fallen.end())
                        continue;

                    auto candidates = dependencies[i];

                    for (auto c : candidates)
                    {
                        auto r_c = r_dependencies[c];

                        bool fall = true;
                        for (auto r_cc : r_c)
                            fall &= (fallen.find(r_cc) != fallen.end());

                        if (fall && (fallen.find(c) == fallen.end()))
                        {
                            fallen.insert(c);
                            chained = true;
                        }
                    }
                }
            }

            // -1 cause the starting brick does not count
            falling += fallen.size() - 1;
        }


        return falling;
    }

public:
    Day22()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_22.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_22.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 22 - Part 1: " << result_1 << '\n'
                  << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY22