#ifndef ADVENTOFCODE2020_DAY19
#define ADVENTOFCODE2020_DAY19

#include "../includes/aoc.h"
#include <regex>

class Day19 {
private:
    struct Rule {
        std::vector<std::vector<int32_t>> subrules;
        uint8_t character;
    };

    std::unordered_map<int32_t, Rule> rules;
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<std::string> messages;

    std::vector<std::string> parse(int rule_id, std::string message)
    {
        Rule& ru = rules[rule_id];
        if (ru.character != 0)
        {
            // return the rest of the message
            if (ru.character == message[0])
                return std::vector<std::string>{ message.substr(1) };
            
            // no match, return no result
            return std::vector<std::string>{ };
        }

        std::vector<std::string> possible_rest_messages{ };

        for (auto& subrule : ru.subrules)
        {
            std::vector<std::string> possibleSuffixes{ message };
            std::vector<std::string> possibleSuffixesAfter{ };

            for (auto id : subrule) 
            {
                for (auto& singleSuffix : possibleSuffixes)
                {
                    auto temp = parse(id, singleSuffix);
                    for (auto& elem : temp)
                    {
                        possibleSuffixesAfter.push_back(elem);
                    }
                }

                possibleSuffixes.clear();
                std::swap(possibleSuffixesAfter, possibleSuffixes);
            }

            for (auto& elem : possibleSuffixes)
            {
                possible_rest_messages.push_back(elem);
            }
        }

        return possible_rest_messages;
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
            else {
                if (elem != "")
                    messages.push_back(elem);
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

        for (auto message : messages)
        {
            auto suffixes = parse(0, message);

            if (std::find(suffixes.begin(), suffixes.end(), "") != suffixes.end())
            {
                result_1++;
            }
        }

        // Change rules according to part 2
        Rule new_8;
        std::vector<int32_t> rule1{ 42 };
        std::vector<int32_t> rule2{ 42, 8 };
        new_8.subrules.push_back(rule1);
        new_8.subrules.push_back(rule2);
        new_8.character = 0;

        rules[8] = new_8;

        Rule new_11;
        std::vector<int32_t> rule1_11{ 42, 31 };
        std::vector<int32_t> rule2_11{ 42, 11, 31 };
        new_11.subrules.push_back(rule1_11);
        new_11.subrules.push_back(rule2_11);
        new_11.character = 0;
        rules[11] = new_11;

        for (auto message : messages)
        {
            auto suffixes = parse(0, message);

            if (std::find(suffixes.begin(), suffixes.end(), "") != suffixes.end())
            {
                result_2++;
            }
        }

        int64_t time = myTime.usPassed();
        std::cout << "Day 19 - Part 1: " << result_1 << '\n'
                  << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY19
