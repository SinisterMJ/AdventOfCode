#ifndef ADVENTOFCODE2022_DAY05
#define ADVENTOFCODE2022_DAY05

#include "../includes/aoc.h"
#include <stack>

class Day05 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<std::stack<int8_t>> crates;

    struct moves {
        int from;
        int to;
        int count;
    };

    std::vector<moves> move_cmds;

    std::string part1()
    {
        bool readCrates = true;
        std::vector<std::stack<int8_t>> crates_in;

        for (auto line : inputVector)
        {
            if (line == "")
                readCrates = false;

            if (readCrates)
            {
                for (int index = 1; index < line.size(); index += 4)
                {
                    if (line[index] == '1')
                        break;

                    if (line[index] != ' ')
                    {
                        if (((index - 1) / 4) + 1 > crates_in.size())
                            crates_in.resize(((index - 1) / 4) + 1);

                        crates_in[((index - 1) /4)].push(line[index]);
                    }
                }
            }
            else
            {
                if (line.find("move") != std::string::npos)
                {
                    moves temp;
                    auto split = util::split(line, ' ');
                    temp.count = std::stoi(split[1]);
                    temp.from = std::stoi(split[3]) - 1;
                    temp.to = std::stoi(split[5]) - 1;

                    move_cmds.push_back(temp);
                }
            }
        }

        crates.resize(crates_in.size());

        for (int index = 0; index < crates_in.size(); ++index)
        {
            while (!crates_in[index].empty())
            {
                crates[index].push(crates_in[index].top());
                crates_in[index].pop();
            }
        }

        auto crates_local = crates;

        for (auto cmd : move_cmds)
        {
            for (int count = 0; count < cmd.count; ++count)
            {
                auto val = crates_local[cmd.from].top();
                crates_local[cmd.from].pop();
                crates_local[cmd.to].push(val);
            }
        }

        std::string result = "";
        for (auto crate : crates_local)
        {
            result += std::string(1, crate.top());
        }

        return result;
    }

    std::string part2()
    {
        auto crates_local = crates;

        for (auto cmd : move_cmds)
        {
            std::stack<int8_t> local;
            for (int count = 0; count < cmd.count; ++count)
            {
                auto val = crates_local[cmd.from].top();
                local.push(val);
                crates_local[cmd.from].pop();
            }

            for (int count = 0; count < cmd.count; ++count)
            {
                auto val = local.top();
                crates_local[cmd.to].push(val);
                local.pop();
            }            
        }

        std::string result = "";
        for (auto crate : crates_local)
        {
            result += std::string(1, crate.top());
        }

        return result;
    }

public:
    Day05()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_5.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY05