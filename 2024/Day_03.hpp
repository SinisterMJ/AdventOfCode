#ifndef ADVENTOFCODE2024_DAY03
#define ADVENTOFCODE2024_DAY03

#include "../includes/aoc.h"
#include <algorithm>
#include <regex>

class Day03 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part(bool do_skip)
    {
        const std::regex r("mul\\(([0-9]+,[0-9]+)\\)");
        std::smatch sm;

        bool enabled = true;

        int64_t result = 0;

        for (auto line : inputVector)
        {
            while (std::regex_search(line, sm, r))
            {
                auto mul_str = sm[1].str();
                auto pos = mul_str.find(',');
                auto front = std::stoi(mul_str.substr(0, pos));
                auto back = std::stoi(mul_str.substr(pos + 1));

                auto prefix_str = sm.prefix().str();

                auto pos_enable = static_cast<int64_t>(prefix_str.rfind("do()"));
                auto pos_disable = static_cast<int64_t>(prefix_str.rfind("don't()"));

                if (pos_disable > pos_enable)
                    enabled = false;

                if (pos_enable > pos_disable)
                    enabled = true;

                if (enabled || do_skip)
                    result += front * back;

                line = sm.suffix().str();
            }
        }

        return result;
    }

public:
    Day03()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_3.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part(true);
        auto result_2 = part(false);

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY03