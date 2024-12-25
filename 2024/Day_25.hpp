#ifndef ADVENTOFCODE2024_DAY25
#define ADVENTOFCODE2024_DAY25

#include "../includes/aoc.h"
#include <algorithm>

class Day25 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::vector<std::vector<int8_t>> keys;
        std::vector<std::vector<int8_t>> locks;

        for (int i = 0; i < inputVector.size(); i += 8)
        {
            // Key
            if (inputVector[i + 6] == "#####")
            {
                std::vector<int8_t> key_temp;                
                for (int j = 0; j < 5; ++j)
                {
                    int8_t depth = 0;

                    depth += (inputVector[i + 1][j] == '#');
                    depth += (inputVector[i + 2][j] == '#');
                    depth += (inputVector[i + 3][j] == '#');
                    depth += (inputVector[i + 4][j] == '#');
                    depth += (inputVector[i + 5][j] == '#');
                    key_temp.push_back(depth);
                }
                keys.push_back(key_temp);
            }
            else // lock
            {
                std::vector<int8_t> lock_temp;
                for (int j = 0; j < 5; ++j)
                {
                    int8_t depth = 0;

                    depth += (inputVector[i + 1][j] == '.');
                    depth += (inputVector[i + 2][j] == '.');
                    depth += (inputVector[i + 3][j] == '.');
                    depth += (inputVector[i + 4][j] == '.');
                    depth += (inputVector[i + 5][j] == '.');
                    lock_temp.push_back(5 - depth);
                }
                locks.push_back(lock_temp);
            }
        }

        int64_t result = 0;
        for (auto& key : keys)
        {
            for (auto& lock : locks)
            {
                if ((key[0] + lock[0] < 6) &&
                    (key[1] + lock[1] < 6) &&
                    (key[2] + lock[2] < 6) &&
                    (key[3] + lock[3] < 6) &&
                    (key[4] + lock[4] < 6))
                    result++;
            }
        }

        return result;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day25()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_25.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_25.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 25 - Part 1: " << result_1 << '\n'
                  << "Day 25 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY25