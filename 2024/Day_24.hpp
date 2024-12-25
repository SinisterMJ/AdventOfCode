#ifndef ADVENTOFCODE2024_DAY24
#define ADVENTOFCODE2024_DAY24

#include "../includes/aoc.h"
#include <algorithm>
#include <bitset>

class Day24 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct gate {
        std::string input_1;
        std::string input_2;
        std::string logic;
        std::string output;
    };

    std::vector<gate> all_gates;
    std::map<std::string, bool> values_orig;

    int64_t get_output() 
    {
        auto values = values_orig;
        bool found_new = true;
        while (found_new)
        {
            found_new = false;

            for (auto& g : all_gates)
            {
                if (values.count(g.output) > 0)
                    continue;

                if (values.count(g.input_1) == 0 || values.count(g.input_2) == 0)
                    continue;

                found_new = true;

                if (g.logic == "AND")
                    values[g.output] = values[g.input_1] && values[g.input_2];
                if (g.logic == "OR")
                    values[g.output] = values[g.input_1] || values[g.input_2];
                if (g.logic == "XOR")
                    values[g.output] = values[g.input_1] ^ values[g.input_2];
            }
        }

        int index = 0;
        std::bitset<64> ringList(0);

        while (true)
        {
            std::string gate_name = "z";
            if (index < 10)
                gate_name += "0";
            gate_name += std::to_string(index);

            if (values.count(gate_name) == 0)
                break;

            ringList[index] = values[gate_name];
            index++;
        }

        return ringList.to_ullong();
    }

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            if (line.find(": ") != std::string::npos)
            {
                auto parts = util::split(line, ": ");
                values_orig[parts[0]] = (parts[1] == "1");
            }

            if (line.find(" -> ") != std::string::npos)
            {
                auto splits = util::split(line, " ");
                gate temp;
                temp.input_1 = splits[0];
                temp.logic = splits[1];
                temp.input_2 = splits[2];
                temp.output = splits[4];
                all_gates.push_back(temp);
            }
        }

        return get_output();
    }

    std::string part2()
    {
        // Solved by hand on paper
        return "ddn,kqh,nhs,nnf,wrc,z09,z20,z34";
    }

public:
    Day24()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_24.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_24.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 24 - Part 1: " << result_1 << '\n'
                  << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY24