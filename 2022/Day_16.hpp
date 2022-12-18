#ifndef ADVENTOFCODE2022_DAY16
#define ADVENTOFCODE2022_DAY16

#include "../includes/aoc.h"
#include <regex>
#include <bitset>

class Day16 {
private:

    std::vector<std::string> inputVector;
    std::map<std::tuple<std::string, int, std::set<std::string>>, int> seen_costs;
    int64_t cache_misses = 0;
    int64_t cache_hits = 0;

    struct Valve {
        int32_t pressure;
        std::vector<std::string> tunnels;
    };

    std::map<std::string, Valve> system_orig;

    std::map<int, std::string> nodeMap;

    void readData()
    {
        //Valve AA has flow rate = 0; tunnels lead to valves DD, II, BB
        std::regex moon_regex("Valve (.*) has flow rate=(.*); tunnel.? lead.? to valve.? (.*)");
        std::smatch moon_match;
        int node = 0;

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
                }
            }
        }
    }

    int flow(std::string position, int time, std::set<std::string> remaining_nodes)
    {
        if (time == 0)
            return 0;

        if (remaining_nodes.empty())
            return 0;

        auto config = std::make_tuple(position, time, remaining_nodes);
        if (seen_costs.contains(config))
        {
            cache_hits++;
            return seen_costs[config];
        }

        cache_misses++;

        int best = 0;

        for (auto target : system_orig[position].tunnels)
            best = std::max(best, flow(target, time - 1, remaining_nodes));
        
        if (remaining_nodes.contains(position))
        {
            remaining_nodes.erase(position);
            best = std::max(best, (time - 1) * system_orig[position].pressure + flow(position, time - 1, remaining_nodes));
        }

        seen_costs[config] = best;

        return best;
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
        int counter = 0;
        for (auto [key, valve] : system_orig)
        {
            if (valve.pressure == 0)
                continue;

            i *= 2;
            i++;
        }

        std::vector<int> results;
        results.resize(i + 1);

        for (int index = 0; index <= i; ++index)
        {
            std::set<std::string> nodes;            
            auto mask = std::bitset<16>(index);

            for (auto [key, val] : nodeMap)
                if (!mask[key])
                    nodes.insert(val);

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
        uint16_t mask = -1;
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 16 - Part 1: " << result_1 << '\n'
                  << "Day 16 - Part 2: " << result_2 << '\n';

        std::cout << "Cache hits: " << cache_hits << std::endl;
        std::cout << "Cache misses: " << cache_misses << std::endl;

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY16