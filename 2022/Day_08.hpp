#ifndef ADVENTOFCODE2022_DAY08
#define ADVENTOFCODE2022_DAY08

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <unordered_map>

class Day08 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::unordered_map<v2, int8_t> trees;
    std::unordered_map<v2, bool> not_seen;

    int part1()
    {
        for (int y = 0; y < inputVector.size(); ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                v2 pos(x, y);
                trees[pos] = inputVector[y][x];
                not_seen[pos] = true;
            }
        }

        int32_t sum = 0;

        for (int y = 0; y < inputVector.size(); ++y)
        {
            int8_t lastHeight = 0;
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                v2 pos(x, y);
                if (trees[pos] > lastHeight)
                {
                    lastHeight = trees[pos];
                    sum += not_seen[pos];
                    not_seen[pos] = false;
                }
            }

            lastHeight = 0;
            for (int x = static_cast<int32_t>(inputVector[y].size()) - 1 ; x >= 0; --x)
            {
                v2 pos(x, y);
                if (trees[pos] > lastHeight)
                {
                    lastHeight = trees[pos];
                    sum += not_seen[pos];
                    not_seen[pos] = false;
                }
            }
        }

        for (int x = 0; x < inputVector[0].size(); ++x)
        {
            int8_t lastHeight = 0;
            for (int y = 0; y < inputVector.size(); ++y)
            {
                v2 pos(x, y);
                if (trees[pos] > lastHeight)
                {
                    lastHeight = trees[pos];
                    sum += not_seen[pos];
                    not_seen[pos] = false;
                }
            }
            lastHeight = 0;
            for (int y = static_cast<int32_t>(inputVector.size()) - 1; y >= 0; --y)
            {
                v2 pos(x, y);
                if (trees[pos] > lastHeight)
                {
                    lastHeight = trees[pos];
                    sum += not_seen[pos];
                    not_seen[pos] = false;
                }
            }
        }

        return sum;
    }

    int64_t part2()
    {
        int64_t best = 0;
        auto neighbours = MapHelper::getNeighboursVec(false);

        for (auto& [start, height] : trees)
        {
            std::vector<int64_t> distances;

            for (auto& direction : neighbours)
            {
                v2 currPos = start;
                while (trees.contains(currPos + direction))
                {
                    currPos = currPos + direction;
                    if (trees[currPos] >= height)
                        break;
                }
                distances.push_back((currPos - start).manhattan());                
            }

            best = std::max<int64_t>(best, distances[0] * distances[1] * distances[2] * distances[3]);
        }

        return best;
    }

public:
    Day08()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_8.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY08