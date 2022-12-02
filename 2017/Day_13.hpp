#ifndef ADVENTOFCODE2017_DAY13
#define ADVENTOFCODE2017_DAY13

#include "../includes/aoc.h"
#include <map>
#include <algorithm>
#include <regex>


class Day13 {
private:
    std::vector<std::string> inputVec;
    struct scanner {
        int depth;
        int range;
    };

    std::vector<scanner> scanners;

    void read_scanners()
    {
        for (auto line : inputVec)
        {
            scanner temp;
            auto scan = util::split(line, ': ');
            temp.depth = std::stoi(scan[0]);
            temp.range = std::stoi(scan[1]);
            scanners.push_back(temp);
        }
    }

    int64_t part1()
    {
        int64_t penalty = 0;
        for (auto scan: scanners)
        {
            int duration = scan.range * 2 - 2;
            if (scan.depth % duration == 0)
                penalty += scan.depth * scan.range;
        }
        return penalty;
    }

    int64_t part2()
    {
        int64_t penalty = 0;
        int64_t offset = 0;
        do
        {
            penalty = 0;
            for (auto scan : scanners)
            {
                int duration = scan.range * 2 - 2;
                if ((scan.depth + offset) % duration == 0)
                    penalty = 1;
            }

            offset++;
        } while (penalty != 0);

        return offset - 1;
    }

public:
    Day13()
    {
        inputVec = util::readFileLines("..\\inputs\\2017\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        read_scanners();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY13