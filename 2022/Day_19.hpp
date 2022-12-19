#ifndef ADVENTOFCODE2022_DAY19
#define ADVENTOFCODE2022_DAY19

#include "../includes/aoc.h"
#include <regex>

class Day19 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Blueprint {
        int ore_robot_cost;
        int clay_robot_cost;
        std::pair<int, int> obsidian_robot_cost;
        std::pair<int, int> geode_robot_cost;

        int max_ore_cost;
        int max_clay_cost;
        int max_obsidian_cost;
    };

    struct Setup {
        int count_ore = 0;
        int count_clay = 0;
        int count_obsidian = 0;
        int count_geode = 0;
        int ore_robots = 1;
        int clay_robots = 0;
        int obsidian_robots = 0;
        int geode_robots = 0;
        int time_remaining = 0;

        bool operator < (const Setup& b) const
        {
            if (count_ore != b.count_ore)
                return count_ore < b.count_ore;

            if (count_clay != b.count_clay)
                return count_clay < b.count_clay;
            
            if (count_obsidian != b.count_obsidian)
                return count_obsidian < b.count_obsidian;
            
            if (count_geode != b.count_geode)
                return count_geode < b.count_geode;
            
            if (ore_robots != b.ore_robots)
                return ore_robots < b.ore_robots;
            
            if (clay_robots != b.clay_robots)
                return clay_robots < b.clay_robots;
            
            if (obsidian_robots != b.obsidian_robots)
                return obsidian_robots < b.obsidian_robots;

            return geode_robots < b.geode_robots;
        }
    };

    std::vector<Blueprint> schemes;

    int max_geodes(int time, Blueprint& scheme)
    {
        Setup conf;
        conf.time_remaining = time;
        std::queue<Setup> q;
        q.push(conf);
        std::set<Setup> seen;
        seen.insert(conf);

        int best = 0;

        while (!q.empty())
        {
            Setup state = q.front();
            q.pop();

            best = std::max(state.count_geode, best);

            if (state.time_remaining == 0 || state.count_geode < (best - 2))
                continue;

            state.time_remaining--;
            

            if (state.count_ore >= scheme.ore_robot_cost && state.ore_robots < scheme.max_ore_cost)
            {
                Setup temp = state;

                temp.count_ore += state.ore_robots;
                temp.count_clay += state.clay_robots;
                temp.count_obsidian += state.obsidian_robots;
                temp.count_geode += state.geode_robots;

                temp.count_ore -= scheme.ore_robot_cost;
                temp.ore_robots += 1;
                if (!seen.contains(temp))
                {
                    seen.insert(temp);
                    q.push(temp);
                }
            }

            if (state.count_ore >= scheme.clay_robot_cost && state.clay_robots < scheme.max_clay_cost)
            {
                Setup temp = state;

                temp.count_ore += state.ore_robots;
                temp.count_clay += state.clay_robots;
                temp.count_obsidian += state.obsidian_robots;
                temp.count_geode += state.geode_robots;

                temp.count_ore -= scheme.clay_robot_cost;
                temp.clay_robots += 1;
                if (!seen.contains(temp))
                {
                    seen.insert(temp);
                    q.push(temp);
                }
            }

            if (state.count_ore >= scheme.obsidian_robot_cost.first && 
                state.count_clay >= scheme.obsidian_robot_cost.second &&
                state.obsidian_robots < scheme.max_obsidian_cost)
            {
                Setup temp = state;

                temp.count_ore += state.ore_robots;
                temp.count_clay += state.clay_robots;
                temp.count_obsidian += state.obsidian_robots;
                temp.count_geode += state.geode_robots;

                temp.count_ore -= scheme.obsidian_robot_cost.first;
                temp.count_clay -= scheme.obsidian_robot_cost.second;
                temp.obsidian_robots += 1;
                if (!seen.contains(temp))
                {
                    seen.insert(temp);
                    q.push(temp);
                }
            }

            if (state.count_ore >= scheme.geode_robot_cost.first &&
                state.count_obsidian >= scheme.geode_robot_cost.second)
            {                
                Setup temp = state;

                temp.count_ore += state.ore_robots;
                temp.count_clay += state.clay_robots;
                temp.count_obsidian += state.obsidian_robots;
                temp.count_geode += state.geode_robots;

                temp.count_ore -= scheme.geode_robot_cost.first;
                temp.count_obsidian -= scheme.geode_robot_cost.second;
                temp.geode_robots += 1;
                if (!seen.contains(temp))
                {
                    seen.insert(temp);
                    q.push(temp);
                }
            }

            state.count_ore += state.ore_robots;
            state.count_clay += state.clay_robots;
            state.count_obsidian += state.obsidian_robots;
            state.count_geode += state.geode_robots;

            if (!seen.contains(state))
            {
                seen.insert(state);
                q.push(state);
            }
        }

        return best;
    }

    int part1()
    {
        // Blueprint 13: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 11 clay. Each geode robot costs 4 ore and 8 obsidian.
        std::regex moon_regex("Blueprint (.*): Each ore robot costs (.*) ore. Each clay robot costs (.*) ore. Each obsidian robot costs (.*) ore and (.*) clay. Each geode robot costs (.*) ore and (.*) obsidian.");
        std::smatch moon_match;
        
        for (auto line : inputVector)
        {
            if (std::regex_search(line, moon_match, moon_regex) && moon_match.size() >= 4)
            {
                Blueprint temp;
                temp.ore_robot_cost = std::stoi(moon_match[2]);
                temp.clay_robot_cost = std::stoi(moon_match[3]);
                temp.obsidian_robot_cost = std::make_pair(std::stoi(moon_match[4]), std::stoi(moon_match[5]));
                temp.geode_robot_cost = std::make_pair(std::stoi(moon_match[6]), std::stoi(moon_match[7]));

                temp.max_ore_cost = temp.clay_robot_cost;
                temp.max_ore_cost = std::max(temp.max_ore_cost, temp.ore_robot_cost);
                temp.max_ore_cost = std::max(temp.max_ore_cost, temp.obsidian_robot_cost.first);
                temp.max_ore_cost = std::max(temp.max_ore_cost, temp.geode_robot_cost.first);
                temp.max_clay_cost = temp.obsidian_robot_cost.second;
                temp.max_obsidian_cost = temp.geode_robot_cost.second;

                schemes.push_back(temp);
            }
        }

        int result = 0;

        for (int index = 0; index < schemes.size(); ++index)
        {
            auto intermediate = max_geodes(24, schemes[index]);
            result += (index + 1) * intermediate;
        }

        std::cout << std::endl;
        return result;
    }

    int part2()
    {
       int result = 1;

        for (int index = 0; index < 3; ++index)
        {
            auto intermediate = max_geodes(32, schemes[index]);
            result *= intermediate;
        }

        return result;
    }

public:
    Day19()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_19.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_19.txt");
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

#endif  // ADVENTOFCODE2022_DAY19