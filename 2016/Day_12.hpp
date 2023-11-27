#ifndef ADVENTOFCODE2016_DAY12
#define ADVENTOFCODE2016_DAY12

#include "../includes/aoc.h"
#include <regex>
#include "../includes/nlohmann/json.hpp"

using json = nlohmann::json;

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct cmd {
        std::string command;
        int8_t reg;
        int8_t source = -1;
        int8_t value;
    };

    std::vector<cmd> command_list;

    void parse_lines()
    {
        for (auto line : inputVec)
        {
            auto els = util::split(line, ' ');
            cmd single;
            single.command = els[0];

            if (single.command == "dec" || single.command == "inc")
            {
                single.reg = els[1][0] - 'a';
            }
            
            if (single.command == "cpy")
            {
                int8_t val = els[1][0] - 'a';

                if (val < 4 && val >= 0)
                    single.source = val;
                else
                    single.value = std::stoi(els[1]);

                single.reg = els[2][0] - 'a';
            }

            if (single.command == "jnz")
            {
                single.reg = els[1][0] - 'a';
                single.value = std::stoi(els[2]);
            }

            command_list.push_back(single);
        }
    }

    int64_t run_parts(int64_t init_c)
    {
        int64_t registers[4];
        std::memset(&registers[0], 0x00, 4 * sizeof(int64_t));
        registers[2] = init_c;

        int index = 0;

        while (index < command_list.size())
        {
            cmd single = command_list[index];

            if (single.command == "inc" || single.command == "dec")
            {
                registers[single.reg] += single.command == "inc" ? 1 : -1;
                index++;
            }
            
            if (single.command == "cpy")
            {
                if (single.source != -1)
                {
                    registers[single.reg] = registers[single.source];
                }
                else
                {
                    registers[single.reg] = single.value;
                }
                index++;
            }

            if (single.command == "jnz")
            {
                if (!in_range<int8_t>(single.reg, 0, 3))
                {
                    index += single.value;
                    continue;
                }
                if (registers[single.reg] != 0)
                {
                    index += single.value;
                }
                else
                {
                    index++;
                }
            }
        }

        return registers[0];
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day12()
    {
        inputString = util::readFile("..\\inputs\\2016\\input_12.txt");
        inputVec = util::readFileLines("..\\inputs\\2016\\input_12.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        parse_lines();
        auto result_1 = run_parts(0);
        auto result_2 = run_parts(1);

        int64_t time = myTime.usPassed();
        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY12
