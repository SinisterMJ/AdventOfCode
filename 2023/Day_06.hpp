#ifndef ADVENTOFCODE2023_DAY06
#define ADVENTOFCODE2023_DAY06

#include "../includes/aoc.h"
#include <algorithm>

class Day06 {
private:

    std::vector<std::string> inputVector;

    int64_t totalVals(int64_t time, int64_t distance)
    {
        double root = std::sqrt(time * time - 4 * distance);
        double result = (time - root) / 2.0;
        return (time - 2 * (int64_t(result) + 1) + 1);
    }

    int64_t part1()
    {
        auto raceTime = util::splitInt64(util::split(inputVector[0], ':')[1], ' ');
        auto raceDistance = util::splitInt64(util::split(inputVector[1], ':')[1], ' ');

        int64_t result = 1;

        for (int index = 0; index < raceTime.size(); ++index)
        {
            auto time = raceTime[index];
            auto distance = raceDistance[index];
            result *= totalVals(time, distance);
        }

        return result;
    }

    int64_t part2()
    {
        auto split = util::split(inputVector[0], ':');
        util::replace(split[1], " ", "");
        int64_t time = std::stoll(split[1]);

        split = util::split(inputVector[1], ':');
        util::replace(split[1], " ", "");
        int64_t distance = std::stoll(split[1]);

        return totalVals(time, distance);
    }

public:
    Day06()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_6.txt");
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

#endif  // ADVENTOFCODE2023_DAY06