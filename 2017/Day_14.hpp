#ifndef ADVENTOFCODE2017_DAY14
#define ADVENTOFCODE2017_DAY14

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

#include <map>
#include <algorithm>


class Day14 {
private:
    std::vector<std::string> input;

    struct command
    {
        std::string cmd;
        std::string reg;
        int offset;
    };

    std::vector<command> cmds;

    void parse_commands()
    {
        for (auto line : input)
        {

        }
    }

    int64_t part1()
    {
        return 0;
    }

    int64_t part2()
    {
        return 0;
    }
public:
	Day14()
	{
		input = util::readFileLines("..\\inputs\\2017\\input_14.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        parse_commands();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY14