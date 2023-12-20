#ifndef ADVENTOFCODE2023_DAY20
#define ADVENTOFCODE2023_DAY20

#include "../includes/aoc.h"
#include <algorithm>

class Day20 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Conjunction {
        std::map<std::string, bool> inputs;
        std::vector<std::string> outputs;
    };

    struct Flipflop {
        std::vector<std::string> outputs;
        bool current_state{ false };
    };

    std::vector<std::string> broadcaster;

    std::map<std::string, Flipflop> flips;
    std::map<std::string, Conjunction> junctions;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            auto parts = util::split(line, " -> ");
            auto receivers = util::split(parts[1], ", ");
            auto name = parts[0].substr(1);

            if (parts[0] == "broadcaster")
                broadcaster = receivers;

            if (parts[0][0] == '&')
                junctions[name].outputs = receivers;

            if (parts[0][0] == '%')
                flips[name].outputs = receivers;
        }

        for (auto& [name, junction] : junctions)
        {
            for (auto [flipName, flip] : flips)
                if (std::find(flip.outputs.begin(), flip.outputs.end(), name) != flip.outputs.end())
                    junction.inputs[flipName] = false;

            for (auto [flipName, flip] : junctions)
                if (std::find(flip.outputs.begin(), flip.outputs.end(), name) != flip.outputs.end())
                    junction.inputs[flipName] = false;
        }

        int64_t low_signals = 0;
        int64_t high_signals = 0;

        for (int index = 0; index < 1000; index++)
        {
            // Button!
            low_signals++;

            std::queue<std::pair<std::pair<std::string, std::string>, bool>> signals;
            for (auto target : broadcaster)
                signals.push(std::make_pair(std::make_pair("", target), false));
            
            while (!signals.empty())
            {
                auto [info, signal] = signals.front(); signals.pop();
                auto [sender, target] = info;
                low_signals += 1 - signal;
                high_signals += signal;

                // Check if conjunction, and handle if so
                if (junctions.find(target) != junctions.end())
                {
                    auto& junction = junctions[target];
                    junction.inputs[sender] = signal;

                    bool all_high = true;
                    for (auto [s, sig] : junction.inputs)
                        all_high &= sig;

                    for (auto receiver : junction.outputs)
                        signals.push(std::make_pair(std::make_pair(target, receiver), !all_high));
                }

                if (flips.find(target) != flips.end())
                {
                    auto& flip = flips[target];
                    if (!signal)
                    {
                        flip.current_state = !flip.current_state;
                        for (auto receiver : flip.outputs)
                            signals.push(std::make_pair(std::make_pair(target, receiver), flip.current_state));                    
                    }
                }
            }
        }

        return low_signals * high_signals;
    }

    int64_t part2()
    {
        junctions.clear();
        flips.clear();

        for (auto line : inputVector)
        {
            auto parts = util::split(line, " -> ");
            auto receivers = util::split(parts[1], ", ");
            auto name = parts[0].substr(1);

            if (parts[0] == "broadcaster")
                broadcaster = receivers;

            if (parts[0][0] == '&')
                junctions[name].outputs = receivers;

            if (parts[0][0] == '%')
                flips[name].outputs = receivers;
        }

        for (auto& [name, junction] : junctions)
        {
            for (auto [flipName, flip] : flips)
                if (std::find(flip.outputs.begin(), flip.outputs.end(), name) != flip.outputs.end())
                    junction.inputs[flipName] = false;

            for (auto [flipName, flip] : junctions)
                if (std::find(flip.outputs.begin(), flip.outputs.end(), name) != flip.outputs.end())
                    junction.inputs[flipName] = false;
        }

        int64_t button_presses = 0;

        int64_t hn = -1;
        int64_t mp = -1;
        int64_t fz = -1;
        int64_t xf = -1;

        for (;;)
        {
            // Button!
            button_presses++;

            std::queue<std::pair<std::pair<std::string, std::string>, bool>> signals;
            for (auto target : broadcaster)
                signals.push(std::make_pair(std::make_pair("", target), false));

            while (!signals.empty())
            {
                auto [info, signal] = signals.front(); signals.pop();
                auto [sender, target] = info;

                if (sender == "hn" && target == "xn" && signal && hn == -1)
                    hn = button_presses;

                if (sender == "xf" && target == "xn" && signal && xf == -1)
                    xf = button_presses;

                if (sender == "fz" && target == "xn" && signal && fz == -1)
                    fz = button_presses;

                if (sender == "mp" && target == "xn" && signal && mp == -1)
                    mp = button_presses;

                if (hn != -1 && xf != -1 && fz != -1 && mp != -1)
                    return lcm(lcm(lcm(hn, xf), fz), mp);

                // Check if conjunction, and handle if so
                if (junctions.find(target) != junctions.end())
                {
                    auto& junction = junctions[target];
                    junction.inputs[sender] = signal;

                    bool all_high = true;
                    for (auto [s, sig] : junction.inputs)
                        all_high &= sig;

                    for (auto receiver : junction.outputs)
                        signals.push(std::make_pair(std::make_pair(target, receiver), !all_high));
                }

                if (flips.find(target) != flips.end())
                {
                    auto& flip = flips[target];
                    if (!signal)
                    {
                        flip.current_state = !flip.current_state;
                        for (auto receiver : flip.outputs)
                            signals.push(std::make_pair(std::make_pair(target, receiver), flip.current_state));
                    }
                }
            }
        }

        return 0;
    }

public:
    Day20()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_20.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_20.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 20 - Part 1: " << result_1 << '\n'
                  << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY20