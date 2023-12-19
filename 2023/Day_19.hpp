#ifndef ADVENTOFCODE2023_DAY19
#define ADVENTOFCODE2023_DAY19

#include "../includes/aoc.h"
#include <algorithm>

class Day19 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct rule {
        int8_t criteria;
        int8_t comparator;
        int32_t value;
        std::string accepted;
    };

    struct ruleSet {
        std::vector<rule> rules;
        std::string rejected;
    };

    std::map<std::string, ruleSet> allRules;

    struct part {
        int32_t x;
        int32_t m;
        int32_t a;
        int32_t s;
    };

    struct ranged_part {
        std::pair<int32_t, int32_t> x;
        std::pair<int32_t, int32_t> m;
        std::pair<int32_t, int32_t> a;
        std::pair<int32_t, int32_t> s;
    };

    std::vector<part> parts;

    bool accepted(part& input, std::string current)
    {
        if (current == "A")
            return true;
        if (current == "R")
            return false;

        auto current_rule = allRules[current];

        for (auto single_rule : current_rule.rules)
        {
            int32_t value = 0;

            if (single_rule.criteria == 'a')
                value = input.a;

            if (single_rule.criteria == 'x')
                value = input.x;

            if (single_rule.criteria == 'm')
                value = input.m;

            if (single_rule.criteria == 's')
                value = input.s;

            if (single_rule.comparator == '>' && value > single_rule.value)
                return accepted(input, single_rule.accepted);

            if (single_rule.comparator == '<' && value < single_rule.value)
                return accepted(input, single_rule.accepted);
        }

        return accepted(input, current_rule.rejected);
    }

    int64_t total_accepted(ranged_part input, std::string current)
    {
        if (current == "A")
        {
            int64_t total_currently = (input.a.second - input.a.first + 1);
            total_currently *= (input.m.second - input.m.first + 1);
            total_currently *= (input.x.second - input.x.first + 1);
            total_currently *= (input.s.second - input.s.first + 1);

            return total_currently;
        }

        if (current == "R")
            return 0;

        int64_t total = 0;
        auto current_rule = allRules[current];

        for (auto single_rule : current_rule.rules)
        {
            ranged_part copy_part = input;
            int32_t value_low = 0;
            int32_t value_high = 0;

            if (single_rule.criteria == 'a')
            {
                value_low = input.a.first;
                value_high = input.a.second;
            }

            if (single_rule.criteria == 'x')
            {
                value_low = input.x.first;
                value_high = input.x.second;
            }

            if (single_rule.criteria == 'm')
            {
                value_low = input.m.first;
                value_high = input.m.second;
            }

            if (single_rule.criteria == 's')
            {
                value_low = input.s.first;
                value_high = input.s.second;
            }

            if (single_rule.comparator == '>')
            {
                if (value_low <= single_rule.value)
                    value_low = single_rule.value + 1;
            }

            if (single_rule.comparator == '<')
            {
                if (value_high >= single_rule.value)
                    value_high = single_rule.value - 1;
            }

            if (single_rule.criteria == 'a')
            {
                copy_part.a.first = value_low;
                copy_part.a.second = value_high;

                if (single_rule.comparator == '>')
                    input.a.second = value_low - 1;
                else
                    input.a.first = value_high + 1;
            }
            
            if (single_rule.criteria == 's')
            {
                copy_part.s.first = value_low;
                copy_part.s.second = value_high;

                if (single_rule.comparator == '>')
                    input.s.second = value_low - 1;
                else
                    input.s.first = value_high + 1;
            }

            if (single_rule.criteria == 'm')
            {
                copy_part.m.first = value_low;
                copy_part.m.second = value_high;

                if (single_rule.comparator == '>')
                    input.m.second = value_low - 1;
                else
                    input.m.first = value_high + 1;
            }
            
            if (single_rule.criteria == 'x')
            {
                copy_part.x.first = value_low;
                copy_part.x.second = value_high;

                if (single_rule.comparator == '>')
                    input.x.second = value_low - 1;
                else
                    input.x.first = value_high + 1;
            }

            if (value_low > value_high)
                return 0;

            total += total_accepted(copy_part, single_rule.accepted);
        }

        if (input.a.first <= input.a.second && input.x.first <= input.x.second && input.s.first <= input.s.second && input.m.first <= input.m.second)
            total += total_accepted(input, current_rule.rejected);
        

        return total;
    }

    int part1()
    {
        bool readingRules = true;

        for (auto& line : inputVector)
        {
            if (line == "")
            {
                readingRules = false;
                continue;
            }

            if (readingRules)
            {
                auto split = util::split(line, '{');
                ruleSet temp;

                split[1] = split[1].substr(0, split[1].size() - 1);
                auto s_rules = util::split(split[1], ',');

                for (int index = 0; index < s_rules.size() - 1; ++index)
                {
                    rule t;
                    t.criteria = s_rules[index][0];
                    t.comparator = s_rules[index][1];
                    auto split_inner = util::split(s_rules[index].substr(2), ':');
                    t.value = std::stoi(split_inner[0]);
                    t.accepted = split_inner[1];

                    temp.rules.push_back(t);
                }

                temp.rejected = s_rules[s_rules.size() - 1];
                
                allRules[split[0]] = temp;
            }
            else
            {
                part temp;
                auto stripped = line.substr(1, line.size() - 2);
                auto vals = util::split(stripped, ',');

                temp.x = std::stoi(vals[0].substr(2));
                temp.m = std::stoi(vals[1].substr(2));
                temp.a = std::stoi(vals[2].substr(2));
                temp.s = std::stoi(vals[3].substr(2));

                parts.push_back(temp);
            }
        }

        int32_t total = 0;

        for (auto p : parts)
        {
            if (accepted(p, "in"))
                total += p.x + p.a + p.m + p.s;
        }

        return total;
    }

    int64_t part2()
    {
        ranged_part start;
        
        start.a = std::make_pair(1, 4000);
        start.x = std::make_pair(1, 4000);
        start.m = std::make_pair(1, 4000);
        start.s = std::make_pair(1, 4000);

        return total_accepted(start, "in");
    }

public:
    Day19()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_19.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_19.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 19 - Part 1: " << result_1 << '\n'
                  << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY19