#ifndef ADVENTOFCODE2021_DAY09
#define ADVENTOFCODE2021_DAY09

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day09 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;
    std::map<v2, int> depth;
    std::vector<v2> neighbours = MapHelper::getNeighboursVec(false);
    std::map<v2, int> basin;
    int id = 0;

    int64_t part1()
    {
        v2 curr_pos(0, 0);

        for (auto line : inputVector)
        {
            curr_pos.x = 0;
            for (auto ch : line)
            {
                int d = ch - '0';

                depth[curr_pos] = d;
                curr_pos.x++;
            }
            curr_pos.y++;
        }

        int result = 0;

        for (auto [pos, d] : depth)
        {
            bool local_deep = true;
            for (auto n : neighbours)
            {
                if (depth.find(pos + n) != depth.end())
                {
                    if (depth[pos + n] <= d)
                        local_deep = false;
                }
            }

            if (local_deep)
            {
                result += d + 1;
                mark_basin(pos, id++);
            }
        }

        return result;
    }

    void mark_basin(v2 start, int ind)
    {
        if (depth[start] == 9)
            return;

        if (basin.find(start) != basin.end())
            return;

        basin[start] = ind;
        for (auto n : neighbours)
        {
            if (depth.find(start + n) != depth.end())
            {
                mark_basin(start + n, ind);
            }
        }
    }

    int64_t part2()
    {
        int result = 0;

        std::vector<int> counts;
        counts.resize(id);

        for (auto [pos, i] : basin)
        {
            counts[i]++;
        }

        std::sort(counts.begin(), counts.end(), std::greater<int>());
        result = counts[0] * counts[1] * counts[2];

        return result;
    }

public:
    Day09()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_9.txt");
        inputVector = util::readFileLines("..\\inputs\\2021\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout 
            << "Day 09 - Part 1: " << result_1 << '\n'
            << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY09