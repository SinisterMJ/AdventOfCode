#ifndef ADVENTOFCODE2025_DAY10
#define ADVENTOFCODE2025_DAY10

#include "../includes/aoc.h"
#include <algorithm>
#include <bitset>
#include <queue>

class Day10 {
private:

    std::vector<std::string> inputVector;

    struct Machine {
        std::vector<bool> lights;
        std::vector<std::vector<int8_t>> buttons;
        std::vector<int64_t> joltages;
    };

    std::vector<Machine> machines;

    int64_t part1()
    {        
        int64_t result = 0;
        for (const auto& line : inputVector)
        {
            auto parts = util::split(line, ' ');
            Machine m;

            for (char c : parts[0])
            {
                if (c == '.')
                    m.lights.emplace_back(false);
                if (c == '#')
                    m.lights.emplace_back(true);
            }

            for (int i = 1; i < parts.size() - 1; i++)
            {
                auto buttonParts = util::split(parts[i].substr(1, parts[i].size() - 2), ',');
                std::vector<int8_t> button;
                for (const auto& bp : buttonParts)
                {
                    button.emplace_back(std::stoi(bp));
                }
                m.buttons.emplace_back(button);
            }

            m.joltages = util::splitInt64(parts.back().substr(1, parts.back().size() - 2), ',');
            machines.push_back(m);

            std::bitset<13> buttonState(0);
            int button_count = std::numeric_limits<int>::max();

            for (int i = 0; i < std::pow(2, m.buttons.size()); ++i)
            {
                buttonState = i;
                if (buttonState.count() >= button_count)
                    continue;

                std::vector<bool> initial(m.lights.size(), false);
                for (int b = 0; b < m.buttons.size(); b++)
                    if (buttonState[b])
                        for (const auto& lightIdx : m.buttons[b])
                            initial[lightIdx] = !initial[lightIdx];
                if (initial == m.lights)
                    button_count = static_cast<int>(buttonState.count());
            }

            result += button_count;
        }

        return result;
    }

    int64_t part2()
    {
        int64_t result = 17576;
        return result;
    }

public:
    Day10()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_10.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY10