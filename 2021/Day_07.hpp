#ifndef ADVENTOFCODE2021_DAY07
#define ADVENTOFCODE2021_DAY07

#include "../includes/aoc.h"

class Day07 {
private:

    std::string inputString;
    std::vector<int32_t> positions;

    int get_distance(int32_t target, bool incremental)
    {
        int fuel = 0;

        for (auto& pos : positions)
        {
            if (incremental)
            {
                auto this_fuel = std::abs(pos - target);
                fuel += (this_fuel * (this_fuel + 1)) / 2;
            }
            else
            {
                fuel += std::abs(pos - target);
            }
        }

        return fuel;
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

        std::sort(positions.begin(), positions.end());

        int32_t sum = 0;
        for (auto pos : positions)
        {
            sum += pos;
        }

        int32_t result_1 = get_distance(positions[positions.size() / 2], false);
        int32_t result_2 = std::min(get_distance(sum / static_cast<int>(positions.size()), true), get_distance(sum / static_cast<int>(positions.size()) + 1, true));

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY07