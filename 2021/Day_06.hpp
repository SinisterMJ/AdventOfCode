#ifndef ADVENTOFCODE2021_DAY06
#define ADVENTOFCODE2021_DAY06

#include "../includes/aoc.h"

class Day06 {
private:

    std::string inputString;

    int64_t solve(int days)
    {
        int64_t result = 0;
        auto ages = util::splitInt(inputString, ',');

        std::map<int8_t, int64_t> fish;

        for (auto age : ages)
            fish[age] += 1;
        
        for (int index = 0; index < days; ++index)
        {
            std::map<int8_t, int64_t> newFish;

            for (auto& [age, number] : fish)
            {
                if (age == 0)
                {
                    newFish[8] += number;
                    newFish[6] += number;
                }
                else
                {
                    newFish[age - 1] += number;
                }
            }

            std::swap(newFish, fish);
        }

        for (auto& [age, number] : fish)
        {
            result += number;
        }

        return result;
    }

public:
    Day06()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(80);
        auto result_2 = solve(256);

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY06