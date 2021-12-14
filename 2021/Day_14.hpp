#ifndef ADVENTOFCODE2021_DAY14
#define ADVENTOFCODE2021_DAY14

#include "../includes/aoc.h"
#include <unordered_map>

class Day14 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::unordered_map<std::string, std::string> rules;
    std::string start = "";

    void build_rules()
    {
        for (auto ln : inputVec)
        {
            if (ln.find("->") != std::string::npos)
            {
                std::string left = ln.substr(0, 2);
                std::string right = ln.substr(ln.size() - 1);

                rules[left] = right;
            }
            else
            {
                start = ln;
            }
        }
    }

    int64_t solve(int rounds)
    {
        std::unordered_map<std::string, int64_t> occurrences;

        for (int i = 0; i < start.size() - 1; ++i)
            occurrences[start.substr(i, 2)]++;

        for (int i = 0; i < rounds; ++i)
        {
            std::unordered_map<std::string, int64_t> temp_occ;
            for (auto [el, val] : occurrences)
            {
                std::string first = el.substr(0, 1) + rules[el];
                std::string second = rules[el] + el.substr(1);

                temp_occ[first] += val;
                temp_occ[second] += val;
            }
            occurrences = std::move(temp_occ);
        }

        std::unordered_map<int8_t, int64_t> counts;

        for (auto [key, val] : occurrences)
            counts[key[0]] += val;

        counts[start[start.size() - 1]]++;

        int64_t max = 0;
        int64_t min = std::numeric_limits<int64_t>::max();

        for (auto [key, val] : counts)
        {
            max = std::max(max, val);
            min = std::min(min, val);
        }

        return max - min;
    }

public:
    Day14()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_14.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_14.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        build_rules();

        auto result_1 = solve(10);
        auto result_2 = solve(40);

        int64_t time = myTime.usPassed();
        std::cout 
            << "Day 14 - Part 1: " << result_1 << '\n'
            << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
