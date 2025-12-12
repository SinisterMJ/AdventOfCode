#ifndef ADVENTOFCODE2025_DAY12
#define ADVENTOFCODE2025_DAY12

#include "../includes/aoc.h"
#include <algorithm>

class Day12 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::map<int, int> patterns;
        int64_t result = 0;
        int index = 0;
        int curr_count = 0;
        for (const auto& line : inputVector)
        {
            if (line.empty())
            {
                patterns[index] = curr_count;
                index++;
                curr_count = 0;
                continue;
            }

            if (line.find("#") != std::string::npos)
            {
                std::string::difference_type n = std::count(line.begin(), line.end(), '#');
                curr_count += static_cast<int>(n);
            }

            if (line.find('x') != std::string::npos)
            {
                auto parts = util::split(line, ": ");
                auto sizes = util::splitInt(parts[0], 'x');
                auto area = sizes[0] * sizes[1];

                auto pattern_counts = util::splitInt(parts[1], ' ');
                int size_needed = 0;
                for (int i = 0; i < pattern_counts.size(); ++i)
                    size_needed += pattern_counts[i] * patterns[i];

                if (size_needed * 1.2 < area)
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
    Day12()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_12.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY12