#ifndef ADVENTOFCODE2017_DAY06
#define ADVENTOFCODE2017_DAY06

#include "../includes/aoc.h"
#include <set>
#include <array>
#include <map>

class Day06 {
private:
    std::string inputString;
    std::vector<std::string> inputVector;
    std::array<int32_t, 16> initial;

    std::pair<int64_t, int64_t> solve()
    {
        int count = 0;
        std::map<std::array<int32_t, 16>, int32_t> seen;
        seen[initial] = 0;

        std::array<int32_t, 16> current;
        std::copy_n(initial.begin(), 16, current.begin());

        while (true)
        {
            int32_t maxBlocks = *std::max_element(current.begin(), current.end());
            int32_t index = 0;
            for (; current[index] != maxBlocks; ++index)
            {
            }

            current[index] = 0;

            for (; maxBlocks > 0; --maxBlocks)
            {
                index = (index + 1) % current.size();
                current[index] += 1;
            }

            ++count;

            if (seen.find(current) != seen.end())
                break;

            seen[current] = count;
        }

        return std::make_pair(count, count - seen[current]);
    }

public:
    Day06()
    {
        inputString = util::readFile("..\\inputs\\2017\\input_6.txt");
        inputVector = util::readFileLines("..\\inputs\\2017\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto numVec = util::splitInt(inputString, '\t');
        std::copy_n(numVec.begin(), 16, initial.begin());

        auto result = solve();
        int64_t result_1 = result.first;
        int64_t result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout 
            << "Day 06 - Part 1: " << result_1 << '\n'
            << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY06