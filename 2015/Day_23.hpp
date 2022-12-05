#ifndef ADVENTOFCODE2015_DAY23
#define ADVENTOFCODE2015_DAY23

#include "../includes/aoc.h"


class Day23 {
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
            auto first = util::split(line, ", ");
            auto order = util::split(first[0], ' ');
            command temp;
            temp.cmd = order[0];
            temp.reg = "";
            temp.offset = 0;
            if (temp.cmd == "jmp")
            {
                temp.offset = std::stoi(order[1]);
            }
            else
            {
                temp.reg = order[1];
            }

            if (first.size() > 1)
                temp.offset = std::stoi(first[1]);

            cmds.push_back(temp);
        }
    }

    int64_t solve(int64_t start)
    {
        int64_t a_reg = start;
        int64_t b_reg = 0;

        int current_instruction = 0;
        
        while (true)
        {
            if (current_instruction >= cmds.size())
                break;

            command curr = cmds[current_instruction];
            int64_t* reg = nullptr;
            if (curr.reg != "")
                reg = (curr.reg == "a") ? &a_reg : &b_reg;

            if (curr.cmd == "hlf")
                *reg = *reg / 2;
            if (curr.cmd == "tpl")
                *reg = *reg * 3;
            if (curr.cmd == "inc")
                *reg = *reg + 1;
            if (curr.cmd == "jmp")
                current_instruction += curr.offset - 1;
            if (curr.cmd == "jie" && (*reg % 2 == 0))
                current_instruction += curr.offset - 1;
            if (curr.cmd == "jio" && ((*reg) == 1))
                current_instruction += curr.offset - 1;

            current_instruction++;
        }

        return b_reg;
    }

public:
    Day23()
    {
        input = util::readFileLines("..\\inputs\\2015\\input_23.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        parse_commands();

        auto result_1 = solve(0);
        auto result_2 = solve(1);

        int64_t time = myTime.usPassed();
        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
            << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2015_DAY23