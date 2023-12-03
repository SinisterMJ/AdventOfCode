#ifndef ADVENTOFCODE2023_DAY02
#define ADVENTOFCODE2023_DAY02

#include "../includes/aoc.h"
#include <algorithm>
#include <tuple>

class Day02 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int result = 0;
        
        std::map<std::string, int> available;
        available["red"] = 12;
        available["green"] = 13;
        available["blue"] = 14;
        
        int index = 1;
        
        for (auto line : inputVector)
        {
            auto games = util::split(line, ':');
            auto draw = util::split(games[1], ';');
            bool passed_test = true;
            for (auto sdraw : draw)
            {
                auto cubes = util::split(sdraw, ',');
                for (auto cube : cubes)
                {
                    if (cube[0] == ' ')
                        cube = cube.substr(1);

                    int64_t pos = cube.find(" ");
                    auto num = cube.substr(0, pos);
                    auto color = cube.substr(pos + 1);
                    if (available[color] < std::stoi(num))
                        passed_test = false;
                }
            }

            if (passed_test)
            {
                result += index;
            }

            ++index;
        }
        return result;
    }

    int64_t part2()
    {
        int result = 0;
        int index = 1;
        for (auto line : inputVector)
        {
            std::map<std::string, int> available;
            available["red"] = 0;
            available["green"] = 0;
            available["blue"] = 0;

            auto games = util::split(line, ':');
            auto draw = util::split(games[1], ';');
            bool failed_test = false;
            for (auto sdraw : draw)
            {
                auto cubes = util::split(sdraw, ',');
                for (auto cube : cubes)
                {
                    if (cube[0] == ' ')
                        cube = cube.substr(1);

                    int64_t pos = cube.find(" ");
                    auto num = std::stoi(cube.substr(0, pos));
                    auto color = cube.substr(pos + 1);
                    available[color] = std::max(num, available[color]);
                }
            }

            result += available["red"] * available["green"] * available["blue"];
        }
        return result;
    }

public:
    Day02()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_2.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << '\n'
                  << "Day 02 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY02