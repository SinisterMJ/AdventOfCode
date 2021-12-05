#ifndef ADVENTOFCODE2021_DAY02
#define ADVENTOFCODE2021_DAY02

#include "../includes/aoc.h"

class Day02 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;

    int64_t forward = 0;
    int64_t depth_1 = 0;
    int64_t depth_2 = 0;

    void solve()
    {
        for (auto line : inputVector)
        {
            if (line.find("forward") != std::string::npos)
            {
                int32_t value = std::stoi(line.substr(8));
                forward += value;
                depth_2 += depth_1 * value;
            }
            if (line.find("down") != std::string::npos)
            {
                depth_1 += std::stoi(line.substr(5));
            }
            if (line.find("up") != std::string::npos)
            {
                depth_1 -= std::stoi(line.substr(3));
            }
        }
    }

public:
    Day02()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_2.txt");
        inputVector = util::readFileLines("..\\inputs\\2021\\input_2.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        solve();

        auto result_1 = forward * depth_1;
        auto result_2 = forward * depth_2;

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << '\n'
                  << "Day 02 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY02