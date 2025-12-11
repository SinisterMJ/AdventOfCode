#ifndef ADVENTOFCODE2025_DAY11
#define ADVENTOFCODE2025_DAY11

#include "../includes/aoc.h"
#include <algorithm>

class Day11 {
private:

    std::vector<std::string> inputVector;
    std::unordered_map<std::string, std::vector<std::string>> connections;

    int64_t path(std::string from, std::string to, std::unordered_map<std::string, int64_t>& costs)
    {
        if (costs.contains(from))
            return costs[from];

        if (from == to)
            return 1;
        
        if (!connections.contains(from))
            return 0;

        int64_t total = 0;
        for (const auto& conn : connections[from])
        {
            total += path(conn, to, costs);
        }

        costs[from] = total;
        
        return total;
    }

    int64_t run_path(std::string from, std::string to)
    {
        std::unordered_map<std::string, int64_t> costs;
        return path(from, to, costs);
    }

    int64_t part1()
    {
        for (const auto& line : inputVector)
        {
            auto parts = util::split(line, ": ");
            auto node = parts[0];
            auto conns = util::split(parts[1], " ");
            connections[node] = conns;
        }

        return run_path("you", "out");
    }

    int64_t part2()
    {
        auto svr_dac = run_path("svr", "dac");
        auto dac_fft = run_path("dac", "fft");
        auto fft_out = run_path("fft", "out");

        auto svr_fft = run_path("svr", "fft");
        auto fft_dac = run_path("fft", "dac");
        auto dac_out = run_path("dac", "out");

        return svr_dac * dac_fft * fft_out + svr_fft * fft_dac * dac_out;
    }

public:
    Day11()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_11.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY11