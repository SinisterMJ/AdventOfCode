#ifndef ADVENTOFCODE2022_DAY23
#define ADVENTOFCODE2022_DAY23

#include "../includes/aoc.h"
#include <map>
#include "../includes/Map2DBase.h"

class Day23 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::pair<int, int> solve()
    {
        std::set<v2> grove;

        int32_t min_y = 0;
        int32_t min_x = 0;
        int32_t max_x = 0;
        int32_t max_y = 0;

        int y_line = 0;
        for (auto line : inputVector)
        {
            int x = 0;
            for (auto ch : line)
            {
                if (ch == '#')
                    grove.insert(v2(x, y_line));
                
                x++;
            }
            max_x = x;
            y_line++;
        }
        max_y = y_line;

        std::vector<std::vector<v2>> rules{ 
            { v2(-1, -1), v2(0, -1), v2(1, -1) },
            { v2(-1, 1), v2(0, 1), v2(1, 1) },
            { v2(-1, -1), v2(-1, 0), v2(-1, 1) },
            { v2(1, -1), v2(1, 0), v2(1, 1) }
        };

        int32_t solve_1;

        std::vector<v2> neighbours = MapHelper::getNeighboursVec(true);
        for (int i = 0;; ++i)
        {
            bool moveHappened = false;
            std::map<v2, int8_t> intermediate;
            std::set<v2> finalGrove;

            for (auto pos : grove)
            {
                bool noNeighbours = true;
                for (auto neigh : neighbours)
                    noNeighbours &= !grove.contains(pos + neigh);
                
                if (noNeighbours)
                    continue;

                for (int rule = 0; rule < 4; ++rule)
                {
                    auto search = rules[(i + rule) % 4];                    
                    bool free = true;
                    for (auto vec : search)
                    {
                        if (grove.contains(pos + vec))
                            free = false;
                    }
                    if (free)
                    {
                        intermediate[pos + search[1]]++;
                        break;
                    }
                }
            }

            for (auto pos : grove)
            {
                bool noNeighbours = true;
                for (auto neigh : neighbours)
                    noNeighbours &= !grove.contains(pos + neigh);

                if (noNeighbours)
                {
                    finalGrove.insert(pos);
                    continue;
                }

                moveHappened = true;
                bool ruleApplied = false;

                for (int rule = 0; rule < 4; ++rule)
                {
                    auto search = rules[(i + rule) % 4];
                    bool free = true;
                    for (auto vec : search)
                    {
                        if (grove.contains(pos + vec))
                            free = false;
                    }
                    if (free)
                    {
                        ruleApplied = true;
                        if (intermediate[pos + search[1]] == 1)
                            finalGrove.insert(pos + search[1]);
                        else
                            finalGrove.insert(pos);
                        break;
                    }
                }
                if (!ruleApplied)
                    finalGrove.insert(pos);
            }

            std::swap(finalGrove, grove);
            min_x = std::numeric_limits<int32_t>::max();
            min_y = std::numeric_limits<int32_t>::max();
            max_x = std::numeric_limits<int32_t>::min();
            max_y = std::numeric_limits<int32_t>::min();
            for (auto& pos : grove)
            {
                min_x = std::min(pos.x, min_x);
                min_y = std::min(pos.y, min_y);
                max_x = std::max(pos.x, max_x);
                max_y = std::max(pos.y, max_y);
            }

            if (i == 9)
                solve_1 = (max_x - min_x + 1) * (max_y - min_y + 1) - static_cast<int32_t>(grove.size());

            if (!moveHappened)
                return std::make_pair(solve_1, i + 1);
        }
    }
    
public:
    Day23()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_23.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_23.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
                  << "Day 23 - Part 2: " << result_2 << '\n';
        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY23