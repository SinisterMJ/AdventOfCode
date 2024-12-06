#ifndef ADVENTOFCODE2024_DAY06
#define ADVENTOFCODE2024_DAY06

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day06 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    Map2DBase<uint8_t> castle;
    std::set<std::pair<v2, v2>> path;

    int64_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                castle.write(v2(x, y), inputVector[y][x]);
            }
        }

        v2 dir(0, -1);
        v2 pos = castle.find('^');

        while (true)
        {
            castle.write(pos, 'X');
            path.insert(std::make_pair(pos, dir));
            v2 new_pos = pos + dir;
            if (!castle.validIndex(new_pos))
                break;
            if (castle.read(new_pos) == '#')
            {
                dir = v2(-dir.y, dir.x);
                continue;
            }

            pos = new_pos;
        }
        
        return castle.findAll('X').size();
    }

    int64_t part2()
    {
        int total = 0;

        std::set<v2> seen_blocks;
        for (const auto& way : path)
        {
            for (int y = 0; y < inputVector.size(); ++y)
            {
                for (int x = 0; x < inputVector[y].size(); ++x)
                {
                    castle.write(v2(x, y), inputVector[y][x]);
                }
            }

            v2 position = way.first + way.second;

            if (castle.read(v2(position)) == '#')
                continue;

            if (seen_blocks.contains(position))
                continue;

            seen_blocks.insert(position);
            castle.write(position, '#');

            v2 dir(0, -1);
            v2 pos = castle.find('^');
            std::set<std::pair<v2, v2>> seen;

            while (true)
            {
                if (seen.contains(std::make_pair(pos, dir)))
                {
                    total += 1;
                    break;
                }
                seen.insert(std::make_pair(pos, dir));
                castle.write(pos, 'X');
                v2 new_pos = pos + dir;
                if (!castle.validIndex(new_pos))
                    break;
                if (castle.read(new_pos) == '#')
                {
                    dir = v2(-dir.y, dir.x);
                    continue;
                }

                pos = new_pos;
            }
        }

        return total;
    }

public:
    Day06()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY06