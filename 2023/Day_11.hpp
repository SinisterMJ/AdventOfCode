#ifndef ADVENTOFCODE2023_DAY11
#define ADVENTOFCODE2023_DAY11

#include "../includes/aoc.h"
#include <algorithm>
#include "../includes/Map2DBase.h"

class Day11 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t solver(int expand)
    {
        std::map<v2, int8_t> base;
        int x_s = 0;
        int y_s = 0;

        for (auto line : inputVector)
        {
            for (auto ch : line)
            {
                base[v2(x_s++, y_s)] = ch;
            }
            x_s = 0;
            y_s++;
        }

        std::vector<v2> galaxies;

        for (auto [pos, val] : base)
            if (val == '#')
                galaxies.push_back(pos);

        for (int64_t y = inputVector.size() - 1; y >= 0; --y)
        {
            bool allEmpty = std::all_of(inputVector[y].begin(), inputVector[y].end(), [](int8_t i) { return i == '.'; });
            if (allEmpty)
                for (auto& pos : galaxies)
                    if (pos.y > y)
                        pos.y += expand - 1;
        }

        for (int x = (int32_t)(inputVector[0].size()) - 1; x >= 0; --x)
        {
            bool allEmpty = true;
            for (int y = 0; y < inputVector.size(); ++y)
                allEmpty &= base[v2(x, y)] == '.';

            if (allEmpty)
                for (auto& pos : galaxies)
                    if (pos.x > x)
                        pos.x += expand - 1;
        }

        int64_t result = 0;
        for (int i = 0; i < galaxies.size(); ++i)
            for (int j = i + 1; j < galaxies.size(); ++j)
                result += (galaxies[i] - galaxies[j]).manhattan();

        return result;
    }

public:
    Day11()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_11.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solver(2);
        auto result_2 = solver(1000000);

        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY11