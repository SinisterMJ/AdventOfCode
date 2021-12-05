#ifndef ADVENTOFCODE2020_DAY24
#define ADVENTOFCODE2020_DAY24

#include "../includes/aoc.h"

class Day24 {
private:
    std::vector<v2> neighbours{ v2(1, 0), v2(1, 1), v2(0, 1), v2(-1, 0), v2(-1, -1), v2(0, -1) };
    enum Direction {
        east,
        southeast,
        southwest,
        west,
        northwest,
        northeast
    };

    void createGrid()
    {
        for (auto& tile : inputVec)
        {
            v2 pos(0, 0);

            for (int index = 0; index < tile.size(); ++index)
            {
                Direction curDir = east;

                if (tile[index] == 'e') curDir = east;
                if (tile[index] == 'w') curDir = west;

                if (tile[index] == 's') {
                    index++;
                    if (tile[index] == 'e') curDir = southeast;
                    if (tile[index] == 'w') curDir = southwest;
                }

                if (tile[index] == 'n') {
                    index++;
                    if (tile[index] == 'e') curDir = northeast;
                    if (tile[index] == 'w') curDir = northwest;
                }

                pos += neighbours[curDir];
            }

            hexGrid[pos] = !hexGrid[pos];
        }
    }

    int64_t part1()
    {
        int64_t result = 0;
        
        for (auto elem : hexGrid)
            result += elem.second;

        return result;
    }

    int64_t part2()
    {
        std::unordered_map<v2, bool> currentGrid = hexGrid;
        std::unordered_map<v2, bool> newGrid;

        for (int days = 0; days < 100; ++days)
        {
            for (auto elem : currentGrid)
            {
                if (elem.second)
                {
                    std::vector<v2> posToCheck{ elem.first };
                    v2 pos = elem.first;

                    for (auto& neighbour : neighbours)
                    {
                        v2 newPos = pos + neighbour;

                        if (newGrid.find(newPos) == newGrid.end())
                            posToCheck.push_back(newPos);
                    }
                                        
                    for (auto& position : posToCheck)
                    {
                        int32_t countPositive = 0;
                        
                        for (auto& neighbour : neighbours)
                        {
                            countPositive += currentGrid[neighbour + position];
                        }

                        if (currentGrid[position])
                        {
                            if (countPositive == 0 || countPositive > 2)
                            {
                                newGrid[position] = false;
                            }
                            else
                            {
                                newGrid[position] = true;
                            }
                        }
                        else
                        {
                            if (countPositive == 2)
                            {
                                newGrid[position] = true;
                            }
                            else
                            {
                                newGrid[position] = false;
                            }
                        }
                    }
                }
            }

            std::swap(currentGrid, newGrid);
            newGrid.clear();
        }

        int64_t result = 0;

        for (auto elem : currentGrid)
            result += elem.second;

        return result;
    }

    std::unordered_map<v2, bool> hexGrid;
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day24()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_24.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_24.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        createGrid();
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 24 - Part 1: " << result_1 << '\n'
                  << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY24
