#ifndef ADVENTOFCODE2022_DAY16
#define ADVENTOFCODE2022_DAY16

#include "../includes/aoc.h"
#include <regex>
#include <bitset>

class Day16 {
private:

    std::vector<std::string> inputVector;
    std::map<std::tuple<std::string, int, std::set<std::string>>, int> seen_costs;

    struct Valve {
        int32_t pressure;
        std::vector<std::string> tunnels;
    };

    std::map<std::string, Valve> system_orig;

    std::map<int, std::string> nodeMap;
    std::map<std::pair<std::string, std::string>, int> valve_matrix;
    std::map<std::set<std::string>, int32_t> costMap;

    int getCosts(std::string start, std::string target)
    {
        int cost = 1;
        std::set<std::string> seen, current;
        seen.insert(start);
        current.insert(start);

        while (true)
        {
            std::set<std::string> new_curr;
            for (auto pos : current)
            {
                for (auto tar : system_orig[pos].tunnels)
                {
                    if (tar == target)
                        return cost;
                    if (!seen.contains(tar))
                    {
                        seen.insert(tar);
                        new_curr.insert(tar);
                    }
                }
            }

            cost++;
            std::swap(current, new_curr);
        }
        return 0;
    }

    void readData()
    {
        //Valve AA has flow rate = 0; tunnels lead to valves DD, II, BB
        std::regex moon_regex("Valve (.*) has flow rate=(.*); tunnel.? lead.? to valve.? (.*)");
        std::smatch moon_match;
        int node = 0;
        std::vector<std::string> valuable_valves{ "AA" };

        for (auto line : inputVector)
        {
            if (std::regex_search(line, moon_match, moon_regex) && moon_match.size() >= 4)
            {
                Valve temp;
                std::string source = moon_match[1];
                temp.pressure = std::stoi(moon_match[2]);
                std::string targets = moon_match[3];
                targets = std::string(" ") + targets;

                auto split = util::split(targets, ',');
                for (auto el : split)
                    temp.tunnels.push_back(el.substr(1));

                system_orig[source] = temp;
                if (temp.pressure > 0)
                {
                    nodeMap[node++] = source;
                    valuable_valves.push_back(source);
                }
            }
        }

        // Create move matrix
        for (int i = 0; i < valuable_valves.size(); ++i)
        {
            for (int j = i + 1; j < valuable_valves.size(); ++j)
            {
                auto res = getCosts(valuable_valves[i], valuable_valves[j]);
                valve_matrix[std::make_pair(valuable_valves[i], valuable_valves[j])] = res;
                valve_matrix[std::make_pair(valuable_valves[j], valuable_valves[i])] = res;
            }
        }
    }

    int flow(std::string position, int time, std::set<std::string> remaining_nodes)
    {
        if (time <= 1)
            return 0;

        if (remaining_nodes.empty())
            return 0;

        auto config = std::make_tuple(position, time, remaining_nodes);
        
        if (seen_costs.contains(config))
        {
            return seen_costs[config];
        }

        int best = 0;

        for (auto target : remaining_nodes)
        {
            if (target == position)
                continue;
            best = std::max(best, flow(target, time - valve_matrix[std::make_pair(position, target)], remaining_nodes));
        }

        if (remaining_nodes.contains(position))
        {
            remaining_nodes.erase(position);
            best = std::max(best, (time - 1) * system_orig[position].pressure + flow(position, time - 1, remaining_nodes));
        }

        seen_costs[config] = best;

        return best;
    }

    void flow_redone(std::string position, int time, std::set<std::string> remaining_nodes, std::set<std::string> visited, int pressure)
    {
        if (remaining_nodes.contains(position))
        {
            time--;
            visited.insert(position);
            pressure += time * system_orig[position].pressure;
            remaining_nodes.erase(position);
        }

        costMap[visited] = std::max(costMap[visited], pressure);

        if (time <= 1 || remaining_nodes.empty())
            return;

        for (auto target : remaining_nodes)
            flow_redone(target, time - valve_matrix[std::make_pair(position, target)], remaining_nodes, visited, pressure);        
    }

    int part1()
    {
        std::set<std::string> nodes;
        for (auto [key, valve] : system_orig)
        {
            if (valve.pressure == 0)
                continue;
            nodes.insert(key);
        }

        return flow("AA", 30, nodes);
    }

    int part2()
    {
        int i = 0;
        for (auto [key, valve] : system_orig)
        {
            if (valve.pressure == 0)
                continue;

            i *= 2;
            i++;
        }

        std::vector<int> results;
        results.resize(i + 1);
        
        {
            std::set<std::string> nodes;
            std::set<std::string> visited;
            visited.insert("AA");
            for (auto& [key, val] : nodeMap)
                nodes.insert(val);

            flow_redone("AA", 26, nodes, std::set<std::string>(), 0);
        }

        int best_redone = 0;

        for (int index = 0; index <= i; ++index)
        {
            std::set<std::string> nodes;
            auto mask = std::bitset<16>(index);

            for (auto [key, val] : nodeMap)
            {
                if (!mask[key])
                    nodes.insert(val);
            }

            if (!costMap.contains(nodes))
                continue;

            for (int index_2 = index + 1; index_2 <= i; ++index_2)
            {
                std::set<std::string> nodes_2;
                auto mask = std::bitset<16>(index);

                for (auto [key, val] : nodeMap)
                {
                    if (!mask[key])
                        nodes_2.insert(val);
                }

                if (!costMap.contains(nodes_2))
                    continue;

                std::set<std::string> intersection;

                std::set_intersection(nodes.begin(), nodes.end(), nodes_2.begin(), nodes_2.end(), std::inserter(intersection, intersection.begin()));

                if (intersection.empty())
                    best_redone = std::max(best_redone, costMap[nodes] + costMap[nodes_2]);
            }
        }

        for (int index = 0; index <= i; ++index)
        {
            std::set<std::string> nodes;            
            auto mask = std::bitset<16>(index);

            for (auto [key, val] : nodeMap)
                if (!mask[key])
                    nodes.insert(val);

            //results[index] = costMap[nodes];
            results[index] = flow("AA", 26, nodes);
        }

        int best = 0;

        for (int index = 0; index < i; ++index)
            best = std::max(best, results[index] + results[i - index]);

        return best;
    }

public:
    Day16()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_16.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        readData();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY16