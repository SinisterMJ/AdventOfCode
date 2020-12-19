#ifndef ADVENTOFCODE2020_DAY19
#define ADVENTOFCODE2020_DAY19

#include "../includes/aoc.h"
#include <regex>

class Day19 {
private:
    struct Rule {
        std::vector<std::vector<int32_t>> subrules;
        uint8_t character;
        std::vector<std::string> allForms;
    };

    std::unordered_map<int32_t, Rule> rules;
    std::string inputString;
    std::vector<std::string> inputVec;

    std::vector<std::string> buildRules(int id) 
    {
        std::vector<std::string> innerResult;
        if (rules[id].character != 0)
        {
            innerResult.push_back(std::string(1, rules[id].character));
            return innerResult;
        }

        if (rules[id].allForms.size() > 0)
            return rules[id].allForms;

        for (auto subList : rules[id].subrules)
        {
            std::vector<std::vector<std::string>> results;
            for (auto elem : subList)
            {
                results.push_back(buildRules(elem));
            }

            if (results.size() > 1)
            {
                for (int i = 0; i < results[0].size(); ++i)
                {
                    for (int j = 0; j < results[1].size(); ++j)
                    {
                        innerResult.push_back(results[0][i] + results[1][j]);
                    }
                }
            }
            else
            {
                for (auto elem : results[0])
                    innerResult.push_back(elem);
            }
        }

        rules[id].allForms = innerResult;
        return rules[id].allForms;
    }

    void readRules() 
    {
        std::regex rule_regex("([0-9]+): (.*)");
        std::smatch rule_match;
        for (auto elem : inputVec)
        {
            if (std::regex_search(elem, rule_match, rule_regex) && rule_match.size() >= 3)
            {
                Rule temp;
                temp.character = 0;
                std::string sub = rule_match[2];
                auto position = sub.find(" | ");
                if (position != std::string::npos)
                {
                    sub.replace(position, 3, "|");
                }

                auto subVec = util::split(sub, '|');

                for (auto subs : subVec)
                {
                    auto innerRules = util::split(subs, ' ');
                    if (in_range(innerRules[0][0], '0', '9'))
                    {
                        std::vector<int32_t> nums;
                        for (auto num : innerRules) {
                            nums.push_back(std::stoi(num));
                        }
                        temp.subrules.push_back(nums);
                    }
                    else
                    {
                        temp.character = subs[1];
                    }
                }

                rules[std::stoi(rule_match[1])] = temp;
            }
        }
    }

public:
    Day19()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_19.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_19.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        readRules();

        auto allPasswords = buildRules(0);

        for (auto message : inputVec)
        {
            if (std::find(allPasswords.begin(), allPasswords.end(), message) != allPasswords.end())
            {
                result_1++;
            }
        }


        int64_t time = myTime.usPassed();
        std::cout << "Day 19 - Part 1: " << result_1 << '\n'
                  << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY19
