#ifndef ADVENTOFCODE2023_DAY15
#define ADVENTOFCODE2023_DAY15

#include "../includes/aoc.h"
#include <algorithm>

class Day15 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int get_hash(std::string input)
    {
        int start = 0;

        for (auto ch : input)
        {
            start += ch;
            start *= 17;
            start %= 256;
        }

        return start;
    }

    int64_t part1()
    {
        auto commands = util::split(inputVector[0], ',');

        int sum = 0;

        for (auto cmd : commands)
            sum += get_hash(cmd);

        return sum;
    }

    int64_t part2()
    {
        auto commands = util::split(inputVector[0], ',');

        std::vector<std::vector<std::pair<std::string, int>>> hashmap;
        hashmap.resize(256);

        for (auto cmd : commands)
        {
            if (cmd.find('=') != std::string::npos)
            {
                auto parts = util::split(cmd, '=');
                int hash = get_hash(parts[0]);
                int lens = std::stoi(parts[1]);

                bool found = false;
                for (auto& [h, l] : hashmap[hash])
                {
                    if (h == parts[0])
                    {
                        l = lens;
                        found = true;
                    }
                }

                if (!found)
                    hashmap[hash].push_back(std::make_pair(parts[0], lens));
            }

            if (cmd.find('-') != std::string::npos)
            {
                auto reg = cmd.substr(0, cmd.size() - 1);
                int hash = get_hash(reg);

                for (int index = 0; index < hashmap[hash].size(); ++index)
                {
                    if (hashmap[hash][index].first == reg)
                    {
                        hashmap[hash].erase(hashmap[hash].begin() + index);
                        break;
                    }
                }
            }
        }

        int64_t total_sum = 0;

        for (int index = 0; index < hashmap.size(); ++index)
            for (int i = 0; i < hashmap[index].size(); ++i)
                total_sum += (index + 1) * (i + 1) * hashmap[index][i].second;

        return total_sum;
    }

public:
    Day15()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_15.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY15