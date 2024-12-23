#ifndef ADVENTOFCODE2024_DAY22
#define ADVENTOFCODE2024_DAY22

#include "../includes/aoc.h"
#include <algorithm>

class Day22 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t secret_num(int64_t input)
    {
        int64_t secret = ((input * 64) ^ input) % 16777216;
        int64_t step_2 = secret / 32;
        secret = (secret ^ step_2) % 16777216;

        return ((secret * 2048) ^ secret) % 16777216;
    }
    int64_t part1()
    {
        int64_t result = 0;
        for (auto& line : inputVector)
        {
            int64_t num = std::stoll(line);

            for (int i = 0; i < 2000; i++)
            {
                num = secret_num(num);
            }

            result += num;
        }

        return result;
    }

    int64_t part2()
    {
        int64_t max_result = 0;
        std::vector<std::vector<int32_t>> differences;
        std::vector<std::vector<int32_t>> monkeys;

        for (auto& line : inputVector)
        {
            int64_t num = std::stoll(line);
            int32_t last = num % 10;
            std::vector<int32_t> temp;
            std::vector<int32_t> temp_m;

            for (int i = 0; i < 2000; i++)
            {
                num = secret_num(num);

                temp.push_back(num % 10 - last);
                temp_m.push_back(num % 10);
                last = num % 10;
            }

            differences.push_back(temp);
            monkeys.push_back(temp_m);
        }

        for (int a = -9; a <= 9; ++a)
        {
            for (int b = -9; b <= 9; ++b)
            {
                if (std::abs(a + b) > 9)
                    continue;
                for (int c = -9; c <= 9; ++c)
                {
                    if (std::abs(c + b) > 9 || std::abs(a + b + c) > 9)
                        continue;
                    for (int d = -9; d <= 9; ++d)
                    {
                        if (std::abs(c + d) > 9 || std::abs(a + b + c + d) > 9 || std::abs(b + c + d) > 9)
                            continue;
                        int64_t result = 0;
                        for (int o = 0; o < differences.size(); ++o)
                        {
                            for (int i = 0; i < 2000 - 4; ++i)
                            {
                                if (differences[o][i + 0] == a &&
                                    differences[o][i + 1] == b &&
                                    differences[o][i + 2] == c &&
                                    differences[o][i + 3] == d)
                                {
                                    result += monkeys[o][i + 3];
                                    break;
                                }
                            }
                        }

                        max_result = std::max(result, max_result);
                    }
                }
            }
        }

        return max_result;
    }

public:
    Day22()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_22.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_22.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 22 - Part 1: " << result_1 << '\n'
                  << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY22