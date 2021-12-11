#ifndef ADVENTOFCODE2021_DAY11
#define ADVENTOFCODE2021_DAY11

#include "../includes/aoc.h"

class Day11 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::pair<int32_t, int32_t> solve()
    {
        std::map<v2, int> octos;
        v2 curr_pos(0, 0);

        for (auto line : inputVec)
        {
            curr_pos.y = 0;
            for (auto ch : line)
            {
                int d = ch - '0';

                octos[curr_pos] = d;
                curr_pos.y++;
            }
            curr_pos.x++;
        }

        int result = 0;
        int result_inner = 0;
        std::vector<v2> neighbours = MapHelper::getNeighboursVec(true);

        for (int i = 1;; ++i)
        {
            if (i == 101)
                result = result_inner;

            for (auto& [pos, charge] : octos)
                charge++;
            
            bool find_max = false;

            do            
            {
                find_max = false;
                for (auto [pos, charge] : octos)
                {
                    if (charge >= 10)
                    {
                        result_inner++;
                        octos[pos] = 0;
                        find_max = true;

                        for (auto n : neighbours)
                            if (octos.find(n + pos) != octos.end() && octos[n + pos] != 0)
                                octos[n + pos]++;
                    }
                }                
            }
            while (find_max);
                        
            int sum = 0;

            for (auto [pos, charge] : octos)
                sum += charge;

            if (sum == 0)
                return std::make_pair(result, i);
        }

        return std::make_pair(0, 0);
    }

public:
    Day11()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();
        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY11