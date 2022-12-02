#ifndef ADVENTOFCODE2022_DAY02
#define ADVENTOFCODE2022_DAY02

#include "../includes/aoc.h"
#include <array>

class Day02 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    struct plays {
        char a;
        char b;
    };

    std::vector<plays> total;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            plays tmp;
            tmp.a = line[0] - 'A';
            tmp.b = line[2] - 'X';
            total.push_back(tmp);
        }

        int local_sum = 0;
        for (auto play : total)
        {
            if (play.a == play.b)
                local_sum += play.b + 1 + 3;

            if (play.a == ((play.b + 1) % 3))
                local_sum += play.b + 1 + 0;

            if (play.a == ((play.b + 2) % 3))
                local_sum += play.b + 1 + 6;
        }

        return local_sum;
    }

    int64_t part2()
    {
        int local_sum = 0;
        std::array<int8_t, 3> offset = { 2, 0, 1 };
        for (auto play : total)
            local_sum += (play.a + offset[play.b]) % 3 + 1 + 3 * play.b;

        return local_sum;
    }

public:
    Day02()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_2.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_2.txt");
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

#endif  // ADVENTOFCODE2022_DAY02