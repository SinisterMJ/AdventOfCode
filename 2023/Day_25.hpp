#ifndef ADVENTOFCODE2023_DAY25
#define ADVENTOFCODE2023_DAY25

#include "../includes/aoc.h"
#include <algorithm>

class Day25 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<std::string, std::vector<std::string>> connections;

    int64_t getNumGroup(std::string node, std::map<std::string, std::vector<std::string>> connections_altered)
    {
        std::set<std::string> localNodes;
        localNodes.insert(node);

        bool added = true;

        while (added)
        {
            added = false;

            for (auto n : localNodes)
            {
                auto targets = connections_altered[n];
                for (auto t : targets)
                {
                    if (!localNodes.contains(t))
                    {
                        added = true;
                        localNodes.insert(t);
                    }
                }
            }
        }

        return localNodes.size();
    }

    int64_t part1()
    {
        std::set<std::string> comp;

        for (auto line : inputVector)
        {
            auto parts = util::split(line, ": ");
            auto subparts = util::split(parts[1], ' ');

            comp.insert(parts[0]);

            for (auto part : subparts)
            {
                connections[part].push_back(parts[0]);
                connections[parts[0]].push_back(part);
                comp.insert(part);
            }
        }

        std::vector<std::string> components(comp.begin(), comp.end());

        for (int i = 0; i < components.size(); ++i)
        {
            auto comp_i = components[i];
            for (int j = i + 1; j < components.size(); ++j)
            {
                auto comp_j = components[j];
                for (int k = j + 1; k < components.size(); ++k)
                {
                    auto comp_k = components[k];
                    for (int i_i = 0; i_i < connections[comp_i].size(); i_i++)
                    {
                        for (int j_i = 0; j_i < connections[comp_j].size(); j_i++)
                        {
                            for (int k_i = 0; k_i < connections[comp_k].size(); k_i++)
                            {
                                auto altered = connections;
                                altered[comp_i].erase(altered[comp_i].begin() + i_i);
                                altered[comp_j].erase(altered[comp_j].begin() + j_i);
                                altered[comp_k].erase(altered[comp_k].begin() + k_i);

                                int64_t groupSize = getNumGroup(components[0], altered);

                                if (groupSize != components.size())
                                {
                                    return (components.size() - groupSize) * groupSize;
                                }

                            }
                        }

                    }
                }
            }
        }

        return 0;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day25()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_25.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_25.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 25 - Part 1: " << result_1 << '\n'
                  << "Day 25 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY25