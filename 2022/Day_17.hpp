#ifndef ADVENTOFCODE2022_DAY17
#define ADVENTOFCODE2022_DAY17

#include "../includes/aoc.h"

class Day17 {
private:

    std::string inputString;

    std::pair<int64_t, int64_t> solve()
    {
        std::vector<std::vector<v2>> rocks{
            { v2(0, 0), v2(1, 0), v2(2, 0), v2(3, 0) },
            { v2(1, 0), v2(0, 1), v2(1, 1), v2(2, 1), v2(1, 2) },
            { v2(2, 2), v2(2, 1), v2(0, 0), v2(1, 0), v2(2, 0) },
            { v2(0, 0), v2(0, 1), v2(0, 2), v2(0, 3) },
            { v2(0, 0), v2(1, 0), v2(0, 1), v2(1, 1) }
        };

        std::set<v2> blocked{ v2(0, -1), v2(1, -1), v2(2, -1), v2(3, -1), v2(4, -1), v2(5, -1), v2(6, -1) };

        v2 lastSpawn(2, 3);
        int64_t currentWind = 0;

        int64_t task_2 = 1000000000000;
        int64_t addedHeight = 0;
        int64_t height_1 = 0;

        std::map<std::tuple<int64_t, int64_t, std::set<v2>>, std::pair<int64_t, int64_t>> repeatable;

        for (int64_t index = 0; index < task_2; ++index)
        {
            auto rock = rocks[index % 5];
            for (auto& stone : rock)
                stone += lastSpawn;

            while (true)
            {
                bool toRight = inputString[currentWind % inputString.size()] == '>';
                currentWind++;
                v2 dir(toRight * 2 - 1, 0);

                bool executable = true;
                for (auto stone : rock)
                    if ((stone + dir).x < 0 || (stone + dir).x > 6 || blocked.contains(stone + dir))
                        executable = false;

                if (executable)
                    for (auto& stone : rock)
                        stone += dir;

                dir = v2(0, -1);

                executable = true;
                for (auto stone : rock)
                    if (blocked.contains(stone + dir))
                        executable = false;

                if (executable)
                    for (auto& stone : rock)
                        stone += dir;
                else
                {
                    for (auto& stone : rock)
                    {
                        blocked.insert(stone);
                        lastSpawn.y = std::max(lastSpawn.y, stone.y + 4);
                    }
                    break;
                }
            }

            // Start memoizing the last 40 lines to check for repititions. 
            // Start earliest in index 2021, as we need that for part1
            if (index >= 2021 && addedHeight == 0)
            {
                //std::set<std::tuple<int64_t, int, std::set<v2>>> repeatable;
                std::set<v2> blocks;
                for (int64_t y = lastSpawn.y; y > lastSpawn.y - 40; --y)
                    for (int x = 0; x < 7; ++x)
                        if (blocked.contains(v2(x, y)))
                            blocks.insert(v2(x, y - lastSpawn.y));

                auto currentInfo = std::make_tuple(index % 5, currentWind % inputString.size(), blocks);
                
                if (repeatable.count(currentInfo) == 0)
                    repeatable[currentInfo] = std::make_pair(lastSpawn.y - 3, index);
                else                    
                { 
                    auto lastSeen = repeatable[currentInfo];

                    int64_t diffHeight = lastSpawn.y - 3 - lastSeen.first;
                    int64_t mult = (task_2 - index) / (index - lastSeen.second);
                    index += mult * (index - lastSeen.second);
                    addedHeight = diffHeight * mult;
                }
            }

            if (index == 2021)
                height_1 = lastSpawn.y - 3;
        }

        return std::make_pair(height_1, lastSpawn.y - 3 + addedHeight);
    }

public:
    Day17()
    {
        inputString = util::readFile("..\\inputs\\2022\\input_17.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 17 - Part 1: " << result_1 << '\n'
                  << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY17