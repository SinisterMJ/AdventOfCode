#ifndef ADVENTOFCODE2020_DAY16
#define ADVENTOFCODE2020_DAY16

#include "../includes/aoc.h"
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

class Day16 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::map<std::string, std::vector<std::pair<int64_t, int64_t>>> values;
    std::vector<std::vector<int64_t>> tickets;

    std::map<int32_t, std::string> keyMap;

    int64_t part1()
    {
        int64_t result = 0;
        std::regex ticket_regex("(.*): ([0-9]*)-([0-9]*) or ([0-9]*)-([0-9]*)");
        std::smatch ticket_match;
        bool startMatching = false;
        for (auto elem : inputVec)
        {
            if (elem.find(" or ") != std::string::npos)
            {
                std::regex_search(elem, ticket_match, ticket_regex);

                std::string key = ticket_match[1];
                std::pair<int64_t, int64_t> lower = std::pair<int64_t, int64_t>(std::stoll(ticket_match[2]), std::stoll(ticket_match[3]));
                std::pair<int64_t, int64_t> higher = std::pair<int64_t, int64_t>(std::stoll(ticket_match[4]), std::stoll(ticket_match[5]));

                values[key].push_back(lower);
                values[key].push_back(higher);
            }

            if (startMatching)
            {
                auto list = util::splitInt64(elem, ',');
                bool validTicket = true;

                for (auto num : list)
                {
                    bool foundRange = false;

                    for (auto key : values)
                    {
                        if (in_range(num, key.second[0].first, key.second[0].second) ||
                            in_range(num, key.second[1].first, key.second[1].second))
                        {
                            foundRange = true;
                            break;
                        }
                    }

                    if (!foundRange)
                    {
                        result += num;
                        validTicket = false;
                    }
                }

                if (validTicket)
                {
                    tickets.push_back(list);
                }
            }

            if (elem.find("nearby tickets:") != std::string::npos)
            {
                startMatching = true;
            }
        }

        return result;
    }

    int64_t part2() 
    {
        int64_t result = 1;
        std::vector<std::pair<std::string, std::set<int8_t>>> setLists;
        for (auto key : values)
        {
            std::set<int8_t> indexes;
            for (int index = 0; index < tickets[0].size(); ++index)
                indexes.insert(index);

            for (auto ticket : tickets)
            {
                std::set<int8_t> valid;
                std::set<int8_t> combined;

                for (int index = 0; index < ticket.size(); ++index)
                {
                    if (in_range(ticket[index], key.second[0].first, key.second[0].second) ||
                        in_range(ticket[index], key.second[1].first, key.second[1].second))
                        valid.insert(index);
                }

                std::set_intersection(indexes.begin(), indexes.end(), valid.begin(), valid.end(), std::inserter(combined, combined.begin()));
                std::swap(combined, indexes);
            }

            setLists.push_back(std::make_pair(key.first, indexes));
        }

        while (setLists.size() > 0)
        {
            for (int index = 0; index < setLists.size(); ++index)
            {
                if (setLists[index].second.size() == 1)
                {
                    auto keyIndex = *(setLists[index].second.begin());
                    keyMap[keyIndex] = setLists[index].first;

                    for (auto& elem : setLists)
                    {
                        elem.second.erase(keyIndex);
                    }

                    setLists.erase(setLists.begin() + index);

                    break;
                }
            }
        }

        for (auto key : keyMap)
        {
            if (key.second.find("departure") != std::string::npos)
            {
                result *= tickets[0][key.first];
            }
        }

        return result;
    }

public:
    Day16()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_16.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_16.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        for (int index = 0; index < inputVec.size(); ++index)
        {
            if (inputVec[index].find("your ticket:") != std::string::npos)
            {
                tickets.push_back(util::splitInt64(inputVec[index + 1], ','));
                break;
            }
        }

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY16
