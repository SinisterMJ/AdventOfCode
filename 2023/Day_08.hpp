#ifndef ADVENTOFCODE2023_DAY08
#define ADVENTOFCODE2023_DAY08

#include "../includes/aoc.h"
#include <algorithm>

class Day08 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<std::string, std::pair<std::string, std::string>> elements;

    int64_t part1()
    {
        std::string instructions = inputVector[0];
        for (auto line : inputVector)
        {
            if (line.find(" = ") == std::string::npos)
                continue;

            auto el = line.substr(0, 3);
            auto el_l = line.substr(7, 3);
            auto el_r = line.substr(12, 3);

            elements[el] = std::make_pair(el_l, el_r);
        }

        std::string curr = "AAA";

        int64_t steps = 0;
        int ins = 0;
        
        while (curr != "ZZZ")
        {
            if (instructions[ins] == 'L')
                curr = elements[curr].first;
            if (instructions[ins] == 'R')
                curr = elements[curr].second;
            
            ++ins;
            ++steps;
            if (ins == instructions.size())
                ins = 0;
        }

        return steps;
    }

    int64_t part2()
    {
        std::vector<std::string> starts;
        for (auto [node, proc] : elements)
        {
            if (node[2] == 'A')
                starts.push_back(node);
        }
        std::string instructions = inputVector[0];


        std::vector<int64_t> steps_ghosts;
        
        for (auto curr : starts)
        {
            int64_t steps = 0;
            int ins = 0;

            while (curr[2] != 'Z')
            {
                if (instructions[ins] == 'L')
                    curr = elements[curr].first;
                if (instructions[ins] == 'R')
                    curr = elements[curr].second;

                ++ins;
                ++steps;
                if (ins == instructions.size())
                    ins = 0;
            }

            steps_ghosts.push_back(steps);
        }

        int64_t result = 1;

        for (auto st : steps_ghosts)
        {
            result = lcm(result, st);
        }

        return result;
    }

public:
    Day08()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY08