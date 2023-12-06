#ifndef ADVENTOFCODE2023_DAY06
#define ADVENTOFCODE2023_DAY06

#include "../includes/aoc.h"
#include <algorithm>

class Day06 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<int> raceTime{ 41, 77, 70, 96 };
    std::vector<int> raceDistance{ 249, 1362, 1127, 1011 };

    int64_t part1()
    {
        int64_t result = 1;

        for (int index = 0; index < raceTime.size(); ++index)
        {
            auto time = raceTime[index];
            auto distance = raceDistance[index];

            int curr_race = 0;
            for (int i = 0; i <= time; ++i)
                curr_race += ((time - i) * i > distance);

            result *= curr_race;
        }

        return result;
    }

    int64_t part2()
    {
        int64_t time = 41777096;
        int64_t distance = 249136211271011;

        double root = std::sqrt(time * time - 4 * distance);
        double result = (time - root) / 2.0;
        return (time - 2 * (int64_t(result) + 1) + 1);
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