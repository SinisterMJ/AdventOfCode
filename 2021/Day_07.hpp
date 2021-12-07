#ifndef ADVENTOFCODE2021_DAY07
#define ADVENTOFCODE2021_DAY07

#include "../includes/aoc.h"

class Day07 {
private:

    std::string inputString;
    std::vector<int32_t> positions;

    int solve(bool incremental)
    {
        int fuel = 0;
        int last_fuel = std::numeric_limits<int>::max();
        for (int i = 0;; ++i)
        { 
            fuel = 0;

            for (auto& pos : positions)
            {
                if (incremental)
                {
                    auto this_fuel = std::abs(pos - i);
                    fuel += (this_fuel * (this_fuel + 1)) / 2;
                }
                else
                {
                    fuel += std::abs(pos - i);
                }                
            }

            if (last_fuel < fuel)
                return last_fuel;

            last_fuel = fuel;
        }

        return 0;
    }

public:
    Day07()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto s_pos = util::split(inputString, ',');
        positions = util::ConvertToInt(s_pos);

        int32_t result_1 = solve(false);
        int32_t result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY07