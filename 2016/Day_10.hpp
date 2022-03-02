#ifndef ADVENTOFCODE2016_DAY10
#define ADVENTOFCODE2016_DAY10

#include "../includes/aoc.h"

class Day10 {
private:
	std::vector<std::string> inputVec;

    std::map<int, std::vector<int>> bot_state;

    struct Bot {
        int id;
        int low = -1;
        int high = -1;
        int output_low = -1;
        int output_high = -1;
    };

    std::map<int, Bot> bot_list;
    
    /*
    value 43 goes to bot 90
    bot 109 gives low to bot 188 and high to bot 13
    */

    void parse_input()
    {
        std::string bot_low = " gives low to bot ";
        std::string out_low = " gives low to output ";
        std::string bot_high = " and high to bot ";
        std::string out_high = " and high to output ";

        for (auto ln : inputVec)
        {
            if (ln.find(" goes to bot ") != std::string::npos)
            {
                auto pos = ln.find(" goes to bot ");
                int val = std::stoi(ln.substr(6, pos - 6));
                int id = std::stoi(ln.substr(pos + std::string(" goes to bot ").size()));

                bot_state[id].push_back(val);
            }
            else
            {
                auto pos_front = ln.find(" gives low to ");
                auto pos_back = ln.find(" and high to ");

                Bot entry;

                entry.id = std::stoi(ln.substr(4, pos_front - 4));

                if (ln.find(bot_low) != std::string::npos)
                {
                    entry.low = std::stoi(ln.substr(pos_front + bot_low.size(), pos_back - pos_front - bot_low.size()));
                }
                else
                {
                    entry.output_low = std::stoi(ln.substr(pos_front + out_low.size(), pos_back - pos_front - out_low.size()));
                }

                if (ln.find(bot_high) != std::string::npos)
                {
                    entry.high = std::stoi(ln.substr(pos_back + bot_high.size(), ln.size() - pos_back - bot_high.size()));
                }
                else
                {
                    entry.output_high = std::stoi(ln.substr(pos_back + out_high.size(), ln.size() - pos_back - out_high.size()));
                }
                

                bot_list[entry.id] = entry;
            }
        }
    }

    int64_t part1()
    {
        parse_input();

        while (true)
        {
            for (auto& [id, vals] : bot_state)
            {
                if (vals.size() == 2)
                { 
                    std::sort(vals.begin(), vals.end());
                    if (vals[0] == 17 && vals[1] == 61)
                        return id;

                    Bot cmd = bot_list[id];

                    if (cmd.low != -1)
                        bot_state[cmd.low].push_back(vals[0]);

                    if (cmd.high != -1)
                        bot_state[cmd.high].push_back(vals[1]);

                    vals.resize(0);
                    break;
                }
            }
        }
    }

    int64_t part2()
    {
        bot_state.clear();
        bot_list.clear();
        parse_input();

        std::map<int, int> output;
        output[0] = -1;
        output[1] = -1;
        output[2] = -1;

        while (output[0] == -1 || output[1] == -1 || output[2] == -1)
        {
            for (auto& [id, vals] : bot_state)
            {
                if (vals.size() == 2)
                {
                    std::sort(vals.begin(), vals.end());

                    Bot cmd = bot_list[id];

                    if (cmd.low != -1)
                        bot_state[cmd.low].push_back(vals[0]);

                    if (cmd.high != -1)
                        bot_state[cmd.high].push_back(vals[1]);

                    if (cmd.output_low != -1)
                        output[cmd.output_low] = vals[0];

                    if (cmd.output_high != -1)
                        output[cmd.output_high] = vals[1];

                    vals.resize(0);
                    break;
                }
            }
        }

        return output[0] * output[1] * output[2];
    }

public:
	Day10()
	{
        inputVec = util::readFileLines("..\\inputs\\2016\\input_10.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY10