#ifndef ADVENTOFCODE2024_DAY19
#define ADVENTOFCODE2024_DAY19

#include "../includes/aoc.h"
#include <algorithm>

class Day19 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        auto hats = util::split(inputVector[0], ", ");
        std::set<std::string> patterns(hats.begin(), hats.end());

        std::vector<std::string> targets;
        std::copy(inputVector.begin() + 2, inputVector.end(), std::back_inserter(targets));

        int result = 0;
        for (auto target : targets)
        {
            std::set<int64_t> seen_offsets;
            std::queue<int64_t> offsets;
            offsets.push(0);
            seen_offsets.insert(0);

            while (!offsets.empty())
            {
                int64_t off = offsets.front(); offsets.pop();
                if (off == static_cast<int64_t>(target.size()))
                {
                    result += 1;
                    break;
                }

                for (auto pattern : patterns)
                {
                    if (target.substr(off, pattern.size()) == pattern && !seen_offsets.contains(off + pattern.size()))
                    {
                        offsets.push(off + pattern.size());
                        seen_offsets.insert(off + pattern.size());
                    }
                }
            }
        }

        return result;
    }

    int64_t part2()
    {

        auto hats = util::split(inputVector[0], ", ");
        std::set<std::string> patterns(hats.begin(), hats.end());

        std::vector<std::string> targets;
        std::copy(inputVector.begin() + 2, inputVector.end(), std::back_inserter(targets));

        int64_t result = 0;
        for (auto target : targets)
        {
            std::map<int64_t, int64_t> seen_offsets;
            seen_offsets[0] = 1;

            for (int64_t index = 1; index <= static_cast<int64_t>(target.size()); ++index)
            {                
                for (auto pattern : patterns)
                {
                    if (index - static_cast<int32_t>(pattern.size()) < 0)
                        continue;

                    if (target.substr(index - pattern.size(), pattern.size()) == pattern)
                        seen_offsets[index] += seen_offsets[index - pattern.size()];
                }
            }

            result += seen_offsets[target.size()];
        }

        return result;
    }

public:
    Day19()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_19.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_19.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 19 - Part 1: " << result_1 << '\n'
                  << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY19