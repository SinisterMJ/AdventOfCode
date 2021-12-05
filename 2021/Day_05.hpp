#ifndef ADVENTOFCODE2021_DAY05
#define ADVENTOFCODE2021_DAY05

#include "../includes/aoc.h"
#include <regex>
#include <vector>
#include <unordered_map>

class Day05 {
private:
    std::vector<std::string> inputs;
    std::string input;
    struct line {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    std::vector<line> allLines;

    void buildLines()
    {
        std::regex line_regex("([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)");
        std::smatch line_match;

        for (auto elem : inputs)
        {
            std::regex_search(elem, line_match, line_regex);
            line entry;
            entry.x1 = std::stoi(line_match[1]);
            entry.y1 = std::stoi(line_match[2]);
            entry.x2 = std::stoi(line_match[3]);
            entry.y2 = std::stoi(line_match[4]);

            allLines.push_back(entry);
        }
    }

    int32_t solve(bool use_diagonals)
    {
        std::unordered_map<v2, int> lines;

        for (auto& line : allLines)
        {
            int32_t x1 = line.x1;
            int32_t y1 = line.y1;
            int32_t x2 = line.x2;
            int32_t y2 = line.y2;

            int slope_x = (x1 == x2) ? 0 : (x2 - x1) / std::abs(x2 - x1);
            int slope_y = (y1 == y2) ? 0 : (y2 - y1) / std::abs(y2 - y1);

            if (slope_x != 0 && slope_y != 0 && !use_diagonals)
                continue;

            for (int32_t i = y1, j = x1;
                i != (y2 + slope_y) || j != (x2 + slope_x);
                i += slope_y, j += slope_x)
            {
                lines[v2(j, i)] = lines[v2(j, i)] + 1;
            }
        }

        int32_t result = 0;
        for (auto& point : lines)
        {
            if (point.second >= 2)
            {
                result++;
            }
        }

        return result;
    }
public:
    Day05()
    {
        inputs = util::readFileLines("..\\inputs\\2021\\input_5.txt", '\n', false);
        input = util::readFile("..\\inputs\\2021\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        buildLines();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout 
            << "Day 05 - Part 1: " << result_1 << '\n'
            << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY05
