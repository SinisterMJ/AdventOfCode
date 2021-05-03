#ifndef ADVENTOFCODE2015_DAY12
#define ADVENTOFCODE2015_DAY12

#include "../includes/aoc.h"
#include <regex>
#include "../includes/nlohmann/json.hpp"

using json = nlohmann::json;

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        std::regex wsaq_re("-?[0-9]+");
        std::regex_token_iterator<std::string::iterator> it(inputString.begin(), inputString.end(), wsaq_re);
        std::regex_token_iterator<std::string::iterator> rend;

        int64_t result = 0;

        while (it != rend)
        {
            int64_t query = std::stoi(*it);
            result += query;
            it++;
        }

        return result;
    }

    static bool has_red_value(const json& _json)
    {
        return std::any_of(_json.cbegin(), _json.cend(), [](const json& value) { return value.is_string() && value.get<std::string>() == "red"; });
    }

    static int64_t calc(const json&  input)
    {
        if (input.is_number())
            return input.get<int>();

        if (input.is_string())
            return 0;

        if (input.is_array() || input.is_object())
        {
            if (input.is_object() && has_red_value(input))
            {
                return 0;
            }

            return std::accumulate(input.cbegin(), input.cend(), static_cast<int64_t>(0), [](int64_t sum, const json& element) { return sum + calc(element); } );
        }

        return 0;
    }

    int64_t part2()
    {
        auto data = json::parse(inputString);
        return calc(data);
    }

public:
    Day12()
    {
        inputString = util::readFile("..\\inputs\\2015\\input_12.txt");
        inputVec = util::readFileLines("..\\inputs\\2015\\input_12.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2015_DAY12
