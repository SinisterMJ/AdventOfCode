#ifndef ADVENTOFCODE2025_DAY05
#define ADVENTOFCODE2025_DAY05

#include "../includes/aoc.h"
#include <algorithm>

class Day05 {
private:

    std::vector<std::string> inputVector;
    std::vector<std::pair<int64_t, int64_t>> ingredients;    

    int64_t part1()
    {
        std::vector<int64_t> available;

        for (const auto& line : inputVector)
        {
            if (line.find('-') != std::string::npos)
            {
                auto ids = util::splitInt64(line, '-');
                ingredients.emplace_back(std::make_pair(ids[0], ids[1]));
            }
            else if (line == "")
                continue;
            else
                available.push_back(std::stoll(line));
        }

        std::sort(ingredients.begin(), ingredients.end());

        for (int i = 0; i < ingredients.size() - 1; ++i)
        {   
            if (overlap<int64_t>(ingredients[i], ingredients[i + 1]))
            {
                ingredients[i] = merge_overlap<int64_t>(ingredients[i], ingredients[i + 1]);
                ingredients.erase(ingredients.begin() + i + 1);
                --i;
            }            
        }        

        int count = 0;
        for (const auto& avail : available)
        {
            for (const auto& ingred : ingredients)
            {
                if (in_range<int64_t>(avail, ingred.first, ingred.second))
                {
                    count++;
                    break;
                }
            }
        }

        return count;
    }

    int64_t part2()
    {
        int64_t count = 0;

        for (const auto& fresh : ingredients)
            count += fresh.second - fresh.first + 1;

        return count;
    }

public:
    Day05()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY05