#ifndef ADVENTOFCODE2017_DAY04
#define ADVENTOFCODE2017_DAY04

#include "../includes/aoc.h"
#include <set>
#include <algorithm>

class Day04 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        int64_t total = 0;

        for (auto& line : inputVec)
        {
            std::set<std::string> seen;
            auto list = util::split(line, ' ');

            bool valid = true;

            for (auto& pw : list)
            {
                if (seen.find(pw) == seen.end())
                {
                    seen.insert(pw);
                }
                else
                {
                    valid = false;
                    break;
                }
            }

            total += valid;
        }

        return total;
    }

    int64_t part2()
    {
        int64_t total = 0;

        for (auto& line : inputVec)
        {
            std::set<std::string> seen;
            auto list = util::split(line, ' ');

            bool valid = true;

            for (auto& pw : list)
            {
                std::sort(pw.begin(), pw.end());
                if (seen.find(pw) == seen.end())
                {
                    seen.insert(pw);
                }
                else
                {
                    valid = false;
                    break;
                }
            }

            total += valid;
        }

        return total;
    }

public:
    Day04()
    {
        inputString = util::readFile("..\\inputs\\2017\\input_4.txt");
        inputVec = util::readFileLines("..\\inputs\\2017\\input_4.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 04 - Part 1: " << result_1 << '\n'
            << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY04
