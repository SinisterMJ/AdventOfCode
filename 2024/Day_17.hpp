#ifndef ADVENTOFCODE2024_DAY17
#define ADVENTOFCODE2024_DAY17

#include "../includes/aoc.h"
#include <algorithm>

class Day17 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::string part1()
    {
        int64_t reg_a = std::stoll(inputVector[0].substr(std::string("Register A: ").size()));
        int64_t reg_b = std::stoll(inputVector[1].substr(std::string("Register B: ").size()));
        int64_t reg_c = std::stoll(inputVector[2].substr(std::string("Register C: ").size()));

        auto commands = util::splitInt64(inputVector[4].substr(std::string("Program: ").size()), ',');

        int64_t command_index = 0;
        std::vector<int32_t> outputs;

        while (command_index < static_cast<int64_t>(commands.size()))
        {
            int64_t combo = commands[command_index + 1];
            if (combo == 4)
                combo = reg_a;
            else if (combo == 5)
                combo = reg_b;
            else if (combo == 6)
                combo = reg_c;

            if (commands[command_index] == 0)
                reg_a = reg_a / (static_cast<int64_t>(0x1) << combo);

            if (commands[command_index] == 1)
                reg_b = reg_b ^ commands[command_index + 1];

            if (commands[command_index] == 2)
                reg_b = combo & 0x7;

            if (commands[command_index] == 3)
            {
                if (reg_a != 0)
                {
                    command_index = commands[command_index + 1];
                    continue;
                }
            }

            if (commands[command_index] == 4)
                reg_b = reg_b ^ reg_c;

            if (commands[command_index] == 5)
                outputs.push_back(combo & 0x7);

            if (commands[command_index] == 6)
                reg_b = reg_a / (static_cast<int64_t>(0x1) << combo);

            if (commands[command_index] == 7)
                reg_c = reg_a / (static_cast<int64_t>(0x1) << combo);

            command_index += 2;
        }

        std::cout << std::endl;

        std::string result = "";
        for (auto v : outputs)
        {
            result += std::to_string(v) + ",";
        }
        result = result.substr(0, result.size() - 1);
        return result;
    }

    int64_t part2()
    {        
        auto commands = util::splitInt64(inputVector[4].substr(std::string("Program: ").size()), ',');

        std::set<int64_t> candidates;
        candidates.insert(0);
        while (true)
        {
            std::set<int64_t> new_gen;
            for (auto value_reg_a: candidates)
            {
                value_reg_a *= 8;
                for (int i = 0; i < 8; ++i)
                {
                    int64_t reg_a = value_reg_a;
                    reg_a += i;

                    int64_t reg_b = 0;
                    int64_t reg_c = 0;

                    int64_t command_index = 0;
                    std::vector<int32_t> outputs;

                    while (command_index < static_cast<int64_t>(commands.size()))
                    {
                        int64_t combo = commands[command_index + 1];
                        if (combo == 4)
                            combo = reg_a;
                        else if (combo == 5)
                            combo = reg_b;
                        else if (combo == 6)
                            combo = reg_c;

                        if (commands[command_index] == 0)
                            reg_a = reg_a / (static_cast<int64_t>(0x1) << combo);

                        if (commands[command_index] == 1)
                            reg_b = reg_b ^ commands[command_index + 1];

                        if (commands[command_index] == 2)
                            reg_b = combo & 0x7;

                        if (commands[command_index] == 3)
                        {
                            if (reg_a != 0)
                            {
                                command_index = commands[command_index + 1];
                                continue;
                            }
                        }

                        if (commands[command_index] == 4)
                            reg_b = reg_b ^ reg_c;

                        if (commands[command_index] == 5)
                            outputs.push_back(combo & 0x7);

                        if (commands[command_index] == 6)
                            reg_b = reg_a / (static_cast<int64_t>(0x1) << combo);

                        if (commands[command_index] == 7)
                            reg_c = reg_a / (static_cast<int64_t>(0x1) << combo);

                        command_index += 2;
                    }

                    if (outputs.size() == commands.size())
                    {
                        bool found = true;
                        for (int index = 0; index < outputs.size(); ++index)
                            found &= (outputs[index] == commands[index]);

                        if (found)
                            return value_reg_a + i;
                    }

                    bool found = true;
                    for (int index = 0; index < outputs.size(); ++index)
                        found &= (outputs[index] == commands[commands.size() - outputs.size() + index]);

                    if (found)
                        new_gen.insert(value_reg_a + i);
                }
            }
            std::swap(new_gen, candidates);
        }
    }

public:
    Day17()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_17.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 17 - Part 1: " << result_1 << '\n'
                  << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY17