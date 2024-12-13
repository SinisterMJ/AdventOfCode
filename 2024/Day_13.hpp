#ifndef ADVENTOFCODE2024_DAY13
#define ADVENTOFCODE2024_DAY13

#include "../includes/aoc.h"
#include <algorithm>

class Day13 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Machine {
        std::pair<int64_t, int64_t> A;
        std::pair<int64_t, int64_t> B;
        std::pair<int64_t, int64_t> target;
    };

    int64_t costA(Machine input)
    {
        int64_t d1 = input.target.first * input.B.second - input.target.second * input.B.first;
        int64_t d2 = input.target.second * input.A.first - input.target.first * input.A.second;
        int64_t d = input.A.first * input.B.second - input.A.second * input.B.first;

        if (d1 % d == 0 && d2 % d == 0)
        {
            return (d1 / d) * 3 + d2 / d;
        }

        return 0;
    }

    int64_t solve(int64_t offset)
    {
        int64_t result = 0;

        for (int i = 0; i < inputVector.size(); i += 4)
        {
            Machine m;
            auto values = inputVector[i].substr(10);
            auto split = util::split(values, ", ");
            auto x_split = util::split(split[0], '+');
            auto y_split = util::split(split[1], '+');

            m.A = std::make_pair(std::stoll(x_split[1]), std::stoll(y_split[1]));


            values = inputVector[i + 1].substr(10);
            split = util::split(values, ", ");
            x_split = util::split(split[0], '+');
            y_split = util::split(split[1], '+');

            m.B = std::make_pair(std::stoll(x_split[1]), std::stoll(y_split[1]));

            values = inputVector[i + 2].substr(7);
            split = util::split(values, ", ");
            x_split = util::split(split[0], '=');
            y_split = util::split(split[1], '=');

            m.target = std::make_pair(std::stoll(x_split[1]) + offset, std::stoll(y_split[1]) + offset);

            result += costA(m);
        }

        return result;
    }


public:
    Day13()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(0);
        auto result_2 = solve(10000000000000);
        int64_t time = myTime.usPassed();

        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY13