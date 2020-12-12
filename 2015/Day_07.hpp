#ifndef ADVENTOFCODE2015_DAY07
#define ADVENTOFCODE2015_DAY07

#include "../includes/aoc.h"
#include <map>
#include <regex>

class Day07 {
private:
    struct Wire {
        uint16_t value;
        std::string instruction;
        bool written;
    };

    std::map<std::string, Wire> allWires;
	std::vector<std::string> inputVec;

    std::regex and_regex;
    std::regex lshift_regex;
    std::regex rshift_regex;
    std::regex or_regex;
    std::regex not_regex;
    std::regex input_regex;

    int16_t ParseWires(std::string node)
    {
        try {
            int val = std::stoi(node);
            return val;
        }
        catch (...) {
        }

        Wire& instance = allWires[node];

        std::smatch reg_match;

        if (instance.written)
            return instance.value;

        std::regex_match(instance.instruction, reg_match, rshift_regex);

        if (reg_match.size() > 1)
        {
            std::string subNode = reg_match[1];
            int shift = std::stoi(reg_match[2]);
            instance.value = ParseWires(subNode) >> shift;
            instance.written = true;
            return instance.value;
        }

        std::regex_match(instance.instruction, reg_match, not_regex);

        if (reg_match.size() > 1)
        {
            std::string subNode = reg_match[1];
            instance.value = 0xFFFF ^ ParseWires(subNode);
            instance.written = true;
            return instance.value;
        }

        std::regex_match(instance.instruction, reg_match, lshift_regex);

        if (reg_match.size() > 1)
        {
            std::string subNode = reg_match[1];
            int shift = std::stoi(reg_match[2]);
         
            instance.value = ParseWires(subNode) << shift;
            instance.written = true;
            return instance.value;
        }

        std::regex_match(instance.instruction, reg_match, input_regex);

        if (reg_match.size() > 1)
        {
            int val = std::stoi(reg_match[1]);

            instance.value = val;
            instance.written = true;
            return instance.value;
        }

        std::regex_match(instance.instruction, reg_match, and_regex);

        if (reg_match.size() > 1)
        {
            std::string subNode_1 = reg_match[1];
            std::string subNode_2 = reg_match[2];

            instance.value = ParseWires(subNode_1) & ParseWires(subNode_2);
            instance.written = true;
            return instance.value;
        }

        std::regex_match(instance.instruction, reg_match, or_regex);

        if (reg_match.size() > 1)
        {
            std::string subNode_1 = reg_match[1];
            std::string subNode_2 = reg_match[2];

            instance.value = ParseWires(subNode_1) | ParseWires(subNode_2);
            instance.written = true;
            return instance.value;
        }

        instance.value = ParseWires(instance.instruction);
        instance.written = true;

        return instance.value;
    }

    int64_t part2(uint16_t in)
    {
        for (auto elem : allWires)
        {
            allWires[elem.first].written = false;
            allWires[elem.first].value = 0;
        }

        allWires["b"].value = in;
        allWires["b"].instruction = std::to_string(in);
        allWires["b"].written = true;

        return ParseWires("a");
    }

    int64_t part1()
    {   
        for (auto elem : inputVec)
        {
            auto splitted = util::split(elem, " -> ");
            Wire temp;
            temp.instruction = splitted[0];
            temp.written = false;

            allWires[splitted[1]] = temp;
        }

        for (auto elem : allWires)
        {
            ParseWires(elem.first);
        }

        return ParseWires("a");
    }
public:
	Day07()
	{
		inputVec = util::readFileLines("..\\inputs\\2015\\input_7.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        and_regex = std::regex("(\\w+) AND (\\w+)");
        lshift_regex = std::regex("(\\w+) LSHIFT ([0-9]+)");
        rshift_regex = std::regex("(\\w+) RSHIFT ([0-9]+)");
        or_regex = std::regex("(\\w+) OR (\\w+)");
        not_regex = std::regex("NOT (\\w+)");
        input_regex = std::regex("([0-9]+)");

        int64_t result_1 = part1();
        int64_t result_2 = part2(static_cast<uint16_t>(result_1));
        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << std::endl
                  << "Day 07 - Part 2: " << result_2 << std::endl;

        return time;
    }
};

#endif  // ADVENTOFCODE2015_DAY07