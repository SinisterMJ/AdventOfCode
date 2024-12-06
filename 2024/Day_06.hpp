#ifndef ADVENTOFCODE2024_DAY06
#define ADVENTOFCODE2024_DAY06

#include "../includes/aoc.h"
#include <algorithm>

class Day06 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::set<std::pair<v2, v2>> path;
    v2 start;

    int64_t part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                if (inputVector[y][x] == '^')
                    start = v2(x, y);
            }
        }

        v2 dir(0, -1);
        v2 pos = start;
        std::set<v2> positions;
        while (true)
        {
            positions.insert(pos);
            path.insert(std::make_pair(pos, dir));
            v2 new_pos = pos + dir;
            if (!in_range<int64_t>(new_pos.y, 0, inputVector.size() - 1) || !in_range<int64_t>(new_pos.x, 0, inputVector[new_pos.y].size() - 1))
                break;

            if (inputVector[new_pos.y][new_pos.x] == '#')
            {
                dir = v2(-dir.y, dir.x);
                continue;
            }

            pos = new_pos;
        }
        
        return positions.size();
    }

    int64_t part2()
    {
        int total = 0;

        std::set<v2> seen_blocks;
        for (const auto& way : path)
        {

            v2 position = way.first + way.second;

            if (inputVector[position.y][position.x] == '#')
                continue;

            if (seen_blocks.contains(position))
                continue;

            seen_blocks.insert(position);
            inputVector[position.y][position.x] = '#';

            v2 dir(0, -1);
            v2 pos = start;
            std::set<std::pair<v2, v2>> seen;

            while (true)
            {
                if (seen.contains(std::make_pair(pos, dir)))
                {
                    total += 1;
                    break;
                }
                seen.insert(std::make_pair(pos, dir));
                v2 new_pos = pos + dir;
                if (!in_range<int64_t>(new_pos.y, 0, inputVector.size() - 1) || !in_range<int64_t>(new_pos.x, 0, inputVector[new_pos.y].size() - 1))
                    break;

                if (inputVector[new_pos.y][new_pos.x] == '#')
                {
                    dir = v2(-dir.y, dir.x);
                    continue;
                }

                pos = new_pos;
            }

            inputVector[position.y][position.x] = '.';
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