#ifndef ADVENTOFCODE2017_DAY13
#define ADVENTOFCODE2017_DAY13

#include "../includes/aoc.h"
#include <map>
#include <algorithm>
#include <regex>


class Day13 {
private:
    std::vector<std::string> inputVec;

    std::map<std::string, std::map<std::string, int32_t>> connections;
    std::set<std::string> names;
    std::vector<std::string> vecNames;

    void buildConnections()
    {
        // Alice would gain 2 happiness units by sitting next to Bob.
        std::regex reg("(\\S+) would (\\S+) ([0-9]+) happiness units by sitting next to (\\S+)\\.");

        std::smatch seating_match;

        for (auto line : inputVec)
        {
            std::regex_search(line, seating_match, reg);

            std::string first_name = seating_match[1];
            bool positive = (seating_match[2] == "gain");
            int32_t value = std::stoi(seating_match[3]);
            std::string second_name = seating_match[4];

            connections[first_name][second_name] = 2 * positive * value - value;

            names.insert(first_name);
        }

        for (auto name : names)
        {
            vecNames.push_back(name);
            connections[name]["me"] = 0;
        }
    }

    int64_t part1()
    {
        std::sort(vecNames.begin(), vecNames.end());
        int64_t maxHappiness = std::numeric_limits<int64_t>::min();

        do
        {
            int64_t currentHappiness = 0;

            for (int index = 0; index < vecNames.size(); ++index)
            {
                auto indexSourceLeft = (index - 1 + vecNames.size()) % vecNames.size();
                auto indexSourceRight = (index + 1) % vecNames.size();

                std::string name = vecNames[index];
                std::string name_left  = vecNames[indexSourceLeft];
                std::string name_right = vecNames[indexSourceRight];

                currentHappiness += connections[name][name_left];
                currentHappiness += connections[name][name_right];
            }

            maxHappiness = std::max(maxHappiness, currentHappiness);
        } while (std::next_permutation(vecNames.begin(), vecNames.end()));

        return maxHappiness;
    }

    int64_t part2()
    {
        vecNames.push_back("me");
        std::sort(vecNames.begin(), vecNames.end());
        int64_t maxHappiness = std::numeric_limits<int64_t>::min();

        do
        {
            int64_t currentHappiness = 0;

            for (int index = 0; index < vecNames.size(); ++index)
            {
                if (vecNames[index] == "me")
                    continue;

                auto indexSourceLeft = (index - 1 + vecNames.size()) % vecNames.size();
                auto indexSourceRight = (index + 1) % vecNames.size();

                std::string name = vecNames[index];
                std::string name_left = vecNames[indexSourceLeft];
                std::string name_right = vecNames[indexSourceRight];

                currentHappiness += connections[name][name_left];
                currentHappiness += connections[name][name_right];
            }

            maxHappiness = std::max(maxHappiness, currentHappiness);
        } while (std::next_permutation(vecNames.begin(), vecNames.end()));

        return maxHappiness;
    }

public:
    Day13()
    {
        inputVec = util::readFileLines("..\\inputs\\2017\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        buildConnections();
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY13