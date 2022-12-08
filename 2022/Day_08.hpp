#ifndef ADVENTOFCODE2022_DAY08
#define ADVENTOFCODE2022_DAY08

#include "../includes/aoc.h"
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
                trees[pos] = inputVector[y][x] - '0';
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
    
    int part2()
    {
        int32_t best = 0;

        for (int y = 0; y < inputVector.size(); ++y)
        {
            for (int x = 0; x < inputVector[y].size(); ++x)
            {
                int32_t view_up = 0, view_down = 0, view_left = 0, view_right = 0;
                v2 currPos(x, y);
                int8_t curr_height = trees[v2(x, y)];

                for (view_up = 1; y - view_up >= 0; ++view_up)
                {
                    v2 pos(x, y - view_up);
                    if (trees[pos] >= curr_height)
                        break;
                }
                view_up -= (y - view_up == -1) ? 1 : 0;

                for (view_down = 1; y + view_down < inputVector.size(); ++view_down)
                {
                    v2 pos(x, y + view_down);
                    if (trees[pos] >= curr_height)
                        break;
                }
                view_down -= (y + view_down == inputVector.size()) ? 1 : 0;

                for (view_left = 1; x - view_left >= 0; ++view_left)
                {
                    v2 pos(x - view_left, y);
                    if (trees[pos] >= curr_height)
                        break;
                }
                view_left -= (x - view_left == -1) ? 1 : 0;

                for (view_right = 1; x + view_right < inputVector[0].size(); ++view_right)
                {
                    v2 pos(x + view_right, y);
                    if (trees[pos] >= curr_height)
                        break;
                }
                view_right -= (x + view_right == inputVector[0].size()) ? 1 : 0;

                best = std::max(best, view_down * view_up * view_left * view_right);
            }
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