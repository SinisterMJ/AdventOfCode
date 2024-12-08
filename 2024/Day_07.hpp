#ifndef ADVENTOFCODE2024_DAY07
#define ADVENTOFCODE2024_DAY07

#include "../includes/aoc.h"
#include <algorithm>
#include <bitset>

class Day07 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    
    int64_t part1()
    {
        std::map<int64_t, std::vector<int64_t>> equations;
        int64_t sum = 0;
        for (auto line : inputVector)
        {
            auto els = util::split(line, ':');
            int64_t left = std::stoll(els[0]);
            auto right = util::splitInt64(els[1], ' ');

            equations[left] = right;
        }

        for (auto [left, right] : equations)
        {
            for (int i = 0; i < (0x1 << (right.size() - 1)); ++i)
            {
                auto binary = std::bitset<16>(i);
                int64_t total = right[0];
                for (int j = 1; j < right.size(); ++j)
                {
                    if (binary[j - 1])
                        total += right[j];
                    else
                        total *= right[j];
                }

                if (total == left)
                {
                    sum += total;
                    break;
                }
            }
        }

        return sum;
    }

    std::string intToTernary(int64_t input)
    {
        std::string result = "";

        if (input == 0)
            return "0";

        while (input != 0)
        {
            auto rest = input % 3;
            result = std::to_string(rest) + result;
            input /= 3;
        }

        return result;
    }

    // generic solution
    template <class T>
    int numDigits(T number)
    {
        int digits = 0;
        if (number == 0)
            return 1;
        while (number) {
            number /= 10;
            digits++;
        }
        return digits;
    }

    int64_t solve_2(int64_t left, std::vector<int64_t>& right, int index, int64_t total)
    {
        if (index == right.size())
            return left == total;

        int64_t result = 0;

        {
            int64_t temp_total = total + right[index];
            result += solve_2(left, right, index + 1, temp_total);
        }

        {
            int64_t temp_total = total * right[index];
            result += solve_2(left, right, index + 1, temp_total);
        }

        {
            int64_t temp_total = total;
            for (int i = 0; i < numDigits(right[index]); ++i)
                temp_total *= 10;

            temp_total += right[index];
            result += solve_2(left, right, index + 1, temp_total);
        }

        return result;
    }

    int64_t part2()
    {
        std::map<int64_t, std::vector<int64_t>> equations;
        int64_t sum = 0;
        for (auto line : inputVector)
        {
            auto els = util::split(line, ':');
            int64_t left = std::stoll(els[0]);
            auto right = util::splitInt64(els[1], ' ');

            equations[left] = right;
        }

        for (auto [left, right] : equations)
        {
            if (solve_2(left, right, 0, 0))
                sum += left;
        }

        return sum;
    }

public:
    Day07()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY07