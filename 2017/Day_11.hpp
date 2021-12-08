#ifndef ADVENTOFCODE2017_DAY11
#define ADVENTOFCODE2017_DAY11

#include "../includes/aoc.h"

class Day11 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::vector<std::string> directions;
    
    std::vector<v2> neighbours{ v2(0, 1), v2(1, 1), v2(1, 0), v2(0, -1), v2(-1, -1), v2(-1, 0) };
    enum Direction {
        north,
        northeast,
        southeast,
        south,
        southwest,
        northwest
    };

    std::pair<int32_t, int32_t> solve()
    {
        v2 position(0, 0);
        int32_t max = 0;

        for (auto& el : directions)
        {
            v2 movement;
            Direction this_dir{ north };

            if (el == "n")
                this_dir = north;
            if (el == "ne")
                this_dir = northeast;
            if (el == "se")
                this_dir = southeast;
            if (el == "s")
                this_dir = south;
            if (el == "sw")
                this_dir = southwest;
            if (el == "nw")
                this_dir = northwest;

            position += neighbours[this_dir];
            max = std::max(max, std::max(std::abs(position.x), std::abs(position.y)));
        }

        int32_t pos_final = std::max(std::abs(position.x), std::abs(position.y));

        return std::make_pair(pos_final, max);
    }

public:
    Day11()
    {
        inputString = util::readFile("..\\inputs\\2017\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2017\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        directions = util::split(inputString, ',');

        auto results = solve();
        auto result_1 = results.first;
        auto result_2 = results.second;

        int64_t time = myTime.usPassed();
        std::cout 
            << "Day 11 - Part 1: " << result_1 << '\n'
            << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY11