#ifndef ADVENTOFCODE2023_DAY13
#define ADVENTOFCODE2023_DAY13

#include "../includes/aoc.h"
#include <algorithm>

class Day13 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::vector<std::map<v2, int8_t>> caves;

    std::string getRow(std::map<v2, int8_t>& cave, int index)
    {
        std::string result = "";
        int x = 0;

        while (cave.find(v2(x, index)) != cave.end())
            result += std::string(1, cave[v2(x++, index)]);

        return result;
    }

    std::string getColumn(std::map<v2, int8_t>& cave, int index)
    {
        std::string result = "";
        int y = 0;

        while (cave.find(v2(index, y)) != cave.end())
            result += std::string(1, cave[v2(index, y++)]);

        return result;
    }

    std::vector<int32_t> valueReflection(std::map<v2, int8_t>& cave)
    {
        std::vector<int32_t> results;

        int index = 1;
        while (getColumn(cave, index) != "")
        {
            if (getColumn(cave, index) == getColumn(cave, index - 1))
            {
                bool found = true;

                int offset = 1;
                while (getColumn(cave, index + offset) != "" && getColumn(cave, index - offset - 1) != "")
                {
                    found &= (getColumn(cave, index + offset) == getColumn(cave, index - offset - 1));
                    ++offset;
                }

                if (found)
                    results.push_back(index);
            }

            ++index;
        }

        index = 1;
        while (getRow(cave, index) != "")
        {
            if (getRow(cave, index) == getRow(cave, index - 1))
            {
                bool found = true;

                int offset = 1;
                while (getRow(cave, index + offset) != "" && getRow(cave, index - offset - 1) != "")
                {
                    found &= (getRow(cave, index + offset) == getRow(cave, index - offset - 1));
                    ++offset;
                }

                if (found)
                    results.push_back(index * 100);
            }

            ++index;
        }

        return results;
    }

    int64_t part1()
    {
        int x = 0;
        int y = 0;
        std::map<v2, int8_t> local;
        int64_t result = 0;

        for (auto line : inputVector)
        {
            if (line == "")
            {
                caves.push_back(local);
                local.clear();
                x = 0;
                y = 0;
                continue;
            }

            
            for (auto ch : line)
                local[v2(x++, y)] = ch;

            x = 0;
            y++;
        }

        caves.push_back(local);

        for (auto cave : caves)
            result += valueReflection(cave)[0];

        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;

        for (auto cave : caves)
        {
            auto orig_result = valueReflection(cave)[0];
            
            for (auto& ch : cave)
            {
                int8_t save = ch.second;
                if (save == '#')
                    ch.second = '.';
                else
                    ch.second = '#';

                auto results = valueReflection(cave);
                if (results.size() == 2)
                {
                    result += results[0] + results[1] - orig_result;
                    break;
                }

                if (results.size() == 1)
                {
                    if (results[0] != orig_result)
                    {
                        result += results[0];
                        break;
                    }
                }

                ch.second = save;
            }
        }

        return result;
    }

public:
    Day13()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY13