#ifndef ADVENTOFCODE2024_DAY03
#define ADVENTOFCODE2024_DAY03

#include "../includes/aoc.h"
#include <algorithm>
#include <regex>

class Day03 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::pair<int64_t, int64_t> part()
    {
        const std::regex r("mul\\((\\d{1,3},\\d{1,3})\\)");
        std::smatch sm;

        bool enabled = true;

        int64_t result_1 = 0;
        int64_t result_2 = 0;

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

                result_1 += front * back;
                if (enabled)
                    result_2 += front * back;

                line = sm.suffix().str();
            }
        }

        return std::make_pair(result_1, result_2);
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

        auto results = part();
        auto result_1 = results.first;
        auto result_2 = results.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY03