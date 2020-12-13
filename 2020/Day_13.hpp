#ifndef ADVENTOFCODE2020_DAY13
#define ADVENTOFCODE2020_DAY13

#include "../includes/aoc.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <execution>
#include <utility>

class Day13 {
private:
    std::vector<int64_t> lines;
    std::vector<int64_t> times;
    
    int mulInv(int64_t a, int64_t b) {
        int b0 = b;
        int x0 = 0;
        int x1 = 1;

        if (b == 1) {
            return 1;
        }

        while (a > 1) {
            int64_t q = a / b;
            int64_t amb = a % b;
            a = b;
            b = amb;

            int64_t xqx = x1 - q * x0;
            x1 = x0;
            x0 = xqx;
        }

        if (x1 < 0) {
            x1 += b0;
        }

        return x1;
    }

    int64_t chineseRemainder(std::vector<int64_t> n, std::vector<int64_t> a) {
        //int64_t prod = std::reduce(std::execution::seq, n.begin(), n.end(), 1, [](int64_t a, int64_t b) { return a * b; });

        int64_t prod = 1;
        
        for (auto elem : n)
            prod *= elem;

        int64_t sm = 0;
        for (int64_t i = 0; i < n.size(); i++) {
            int64_t p = prod / n[i];
            sm += a[i] * mulInv(p, n[i])*p;
        }

        return sm % prod;
    }

    void ReadBusses()
    {
        auto buses = util::split(inputVec[1], ',');

        int index = 0;
        for (auto elem : buses)
        {
            if (elem != "x")
            {
                lines.push_back(std::stoi(elem));
                int32_t modulo = lines.back() - index;
                times.push_back(modulo);
            }
            index++;
        }
    }

    int64_t part1()
    {
        uint32_t depTime = std::stoi(inputVec[0]);

        for (int index = depTime; ; ++index)
        {
            for (auto elem : lines)
            {
                if (index % elem == 0)
                {
                    return elem * (index - depTime);
                }
            }
        }

        return -1;
    }

    int64_t part2()
    {
        auto result = chineseRemainder(lines, times);
        return result;
    }

    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day13()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_13.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_13.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        ReadBusses();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY13
