#ifndef ADVENTOFCODE2022_DAY16
#define ADVENTOFCODE2022_DAY16

#include "../includes/aoc.h"
#include <regex>
#include <bitset>

class Day16 {
private:

    std::vector<std::string> inputVector;

    struct Valve {
        int64_t pressure;
        std::vector<std::string> tunnels;
    };

    std::map<std::string, Valve> system_orig;

    struct State {
        int timePassed = 0;
        int32_t max_pressure = 0;
        int32_t current_pressure = 0;
        std::set<std::string> openValves;
        std::string currentValve = "";

        bool operator < (const State& b) const
        {
            if (max_pressure != b.max_pressure)
                return max_pressure < b.max_pressure;
            if (timePassed != b.timePassed)
                return timePassed < b.timePassed;
            if (current_pressure != b.current_pressure)
                return current_pressure < b.current_pressure;
            if (currentValve != b.currentValve)
                return currentValve < b.currentValve;
            return openValves.size() < b.openValves.size();
        }
    };

    struct ValveState {
        std::set<std::string> openValves;
        std::string currentValve = "";
        std::string currentValveEl = "";

        bool operator < (const ValveState& b) const
        {
            if (currentValve != b.currentValve)
                return currentValve < b.currentValve;
            if (currentValveEl != b.currentValveEl)
                return currentValveEl < b.currentValveEl;
            return openValves.size() < b.openValves.size();
        }
    };

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

    int flow(int time, std::bitset<16> mask)
    {
        std::set<State> seen;
        auto system = system_orig;

        for (auto [key, val] : nodeMap)
        {
            if (!mask[key])
                system[val].pressure = 0;
        }

        int max_press_possible = 0;
        for (auto [key, val] : system)
            max_press_possible += val.pressure;

        State start;
        start.max_pressure = max_press_possible * time;
        start.currentValve = "AA";
        start.current_pressure = 0;
        start.timePassed = 0;

        std::priority_queue<State> workerQueue;

        seen.insert(start);
        workerQueue.push(start);

        int maxVal = 0;

        while (!workerQueue.empty())
        {
            auto curr = workerQueue.top();
            workerQueue.pop();

            curr.max_pressure -= max_press_possible - curr.current_pressure;
            curr.timePassed++;

            if (curr.current_pressure == max_press_possible)
            {
                maxVal = std::max(maxVal, curr.max_pressure);
                continue;
            }

            if (curr.timePassed == time)
            {
                maxVal = std::max(maxVal, curr.max_pressure);
                continue;
            }

            if (maxVal > curr.max_pressure)
                continue;

            if (system[curr.currentValve].pressure > 0 && !curr.openValves.contains(curr.currentValve))
            {
                State tempTarget = curr;
                tempTarget.current_pressure += system[tempTarget.currentValve].pressure;
                tempTarget.openValves.insert(tempTarget.currentValve);
                if (!seen.contains(tempTarget))
                {
                    workerQueue.push(tempTarget);
                    seen.insert(tempTarget);
                }
            }

            for (auto target : system[curr.currentValve].tunnels)
            {
                State newTarget = curr;
                newTarget.currentValve = target;
                if (!seen.contains(newTarget))
                {
                    workerQueue.push(newTarget);
                    seen.insert(newTarget);
                }
            }
        }

        return maxVal;
    }

    int64_t part1()
    {
        uint16_t mask = std::numeric_limits<uint16_t>::max();
        return flow(30, std::bitset<16>(mask));
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

        std::map<int, int> results;

        for (int index = 0; index <= i; ++index)
        {
            results[index] = flow(26, std::bitset<16>(index));
        }

        int best = 0;

        for (int index = 0; index < i; ++index)
        {
            best = std::max(best, results[index] + results[i - index]);
        }

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

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY16