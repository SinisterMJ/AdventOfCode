#ifndef ADVENTOFCODE2025_DAY06
#define ADVENTOFCODE2025_DAY06

#include "../includes/aoc.h"
#include <algorithm>

class Day06 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::vector<std::vector<int64_t>> values;
        std::vector<std::string> operators;
        for (const std::string& line : inputVector)
        {
            std::vector<int64_t> row;
            if (line.find('+') == std::string::npos)
            {
                row = util::splitInt64(line, ' ');
                values.emplace_back(row);
            }
            else
            {
                operators = util::split(line, ' ');
            }            
        }

        int64_t result = 0;

        for (int i = 0; i < operators.size(); ++i)
        {
            int64_t sum = values[0][i];
            if (operators[i] == "+")
                for (int j = 1; j < values.size(); ++j)
                    sum += values[j][i];
            else
                for (int j = 1; j < values.size(); ++j)
                    sum *= values[j][i];

            result += sum;
        }

        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;
        int last_index = 0;

        for (int i = 1; i <= inputVector[4].size(); ++i)
        {
            if (i != inputVector[4].size() && inputVector[4][i] == ' ')
                continue;

            std::vector<int64_t> nums;
            for (int j = last_index; j < i; ++j)
            {
                std::string num = "";
                num += inputVector[0][j];
                num += inputVector[1][j];
                num += inputVector[2][j];
                num += inputVector[3][j];

                if (num == "    ")
                    continue;

                nums.push_back(std::stoll(num));
            }

            int64_t sum = nums[0];
            if (inputVector[4][last_index] == '+')
                for (int j = 1; j < nums.size(); ++j)
                    sum += nums[j];
            else
                for (int j = 1; j < nums.size(); ++j)
                    sum *= nums[j];

            last_index = i;

            result += sum;
        }

        return result;
    }

public:
    Day06()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_6.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY06