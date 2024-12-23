#ifndef ADVENTOFCODE2024_DAY23
#define ADVENTOFCODE2024_DAY23

#include "../includes/aoc.h"
#include <algorithm>

class Day23 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::vector<std::pair<std::string, std::string>> connections;
    std::map<std::string, std::vector<std::string>> connected_systems;
    std::vector<std::string> nodes;

    int64_t part1()
    {
        std::set<std::string> nodes_temp;
        for (auto line : inputVector)
        {
            auto lan = util::split(line, '-');
            connections.push_back(std::make_pair(lan[0], lan[1]));
            nodes_temp.insert(lan[0]);
            nodes_temp.insert(lan[1]);
        }

        std::vector<std::string> v(nodes_temp.begin(), nodes_temp.end());
        nodes = v;

        for (auto& conn : connections)
        {
            auto left = conn.first;
            auto right = conn.second;

            if (connected_systems.count(left) == 0)
                connected_systems[left] = std::vector<std::string>{ right };
            else
                connected_systems[left].push_back(right);

            if (connected_systems.count(right) == 0)
                connected_systems[right] = std::vector<std::string>{ left };
            else
                connected_systems[right].push_back(left);
        }

        int64_t result = 0;

        std::set<std::vector<std::string>> circuits;

        for (auto& [left, list] : connected_systems)
        {
            if (left[0] != 't')
                continue;

            for (auto& conn_1 : list)
            {
                auto& r_list = connected_systems[conn_1];
                for (auto& conn_2 : r_list)
                {
                    if (std::find(list.begin(), list.end(), conn_2) != list.end())
                    {
                        std::vector<std::string> l{ left, conn_1, conn_2 };
                        std::sort(l.begin(), l.end());
                        circuits.insert(l);
                    }
                }
            }
        }

        return circuits.size();
    }

    bool in_clique(std::vector<std::string>& candidates)
    {
        bool found_in_all = true;

        for (int i = 0; i < candidates.size(); ++i)
        {
            for (int j = i + 1; j < candidates.size(); ++j)
            {
                found_in_all &= (
                    std::find(connected_systems[candidates[i]].begin(), connected_systems[candidates[i]].end(), candidates[j])
                    != connected_systems[candidates[i]].end()
                );
            }
        }

        return found_in_all;
    }

    std::string part2()
    {
        std::map<int32_t, int32_t> depth_index;
        depth_index[0] = 0;
        int32_t max_key = 0;

        std::vector<std::string> longest_copy;
        std::vector<std::string> working_nodes;

        while (max_key >= 0)
        {
            working_nodes.clear();
            for (auto [depth, index] : depth_index)
            {
                working_nodes.push_back(nodes[index]);
            }

            if (in_clique(working_nodes))
            {
                if (working_nodes.size() > longest_copy.size())
                    longest_copy = working_nodes;

                depth_index[max_key + 1] = depth_index[max_key] + 1;
                max_key++;
                while (depth_index[max_key] == nodes.size() && max_key >= 0)
                {
                    depth_index.erase(max_key);
                    max_key--;
                    depth_index[max_key]++;
                }
            }
            else
            {
                depth_index[max_key]++;
                while (depth_index[max_key] == nodes.size() && max_key >= 0)
                {
                    depth_index.erase(max_key);
                    max_key--;                    
                    depth_index[max_key]++;
                }
            }
        }

        std::string result = "";
        for (auto& n : longest_copy)
            result += n + ",";
        return result;
    }

public:
    Day23()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_23.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_23.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
                  << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY23