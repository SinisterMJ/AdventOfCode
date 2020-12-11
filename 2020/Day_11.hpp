#ifndef ADVENTOFCODE2020_DAY11
#define ADVENTOFCODE2020_DAY11

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day11 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t runFerry(int max_occupied, int max_vector)
    {
        Map2DBase<int8_t> ferry('.');
        Map2DBase<int8_t> ferry_temp('.');

        std::vector<v2> neighbours = ferry.getNeighboursVec(true);

        for (int y = 0; y < inputVec.size(); ++y)
        {
            for (int x = 0; x < inputVec[y].length(); ++x)
            {
                ferry.write(x, y, inputVec[y][x]);
            }
        }

        bool changed = true;
        while (changed)
        {
            changed = false;

            for (int y = 0; y <= ferry.maxY(); ++y)
            {
                for (int x = 0; x <= ferry.maxX(); ++x)
                {
                    v2 pos(x, y);
                    ferry_temp.write(x, y, ferry.read(x, y));

                    if (ferry.read(x, y) == '.')
                        continue;

                    bool occupied = (ferry.read(x, y) == '#');

                    int32_t count_neighbour = 0;

                    for (auto& elem : neighbours)
                    {
                        for (int index = 1; index <= max_vector; ++index)
                        {
                            v2 pos_neighbour = pos + elem * index;
                            if (pos_neighbour.x >= 0 && pos_neighbour.x <= ferry.maxX() &&
                                pos_neighbour.y >= 0 && pos_neighbour.y <= ferry.maxY())
                            {
                                if (ferry.read(pos_neighbour.x, pos_neighbour.y) != '.')
                                {
                                    count_neighbour += (ferry.read(pos_neighbour.x, pos_neighbour.y) == '#');
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    if (occupied && count_neighbour >= max_occupied)
                    {
                        ferry_temp.write(x, y, 'L');
                        changed = true;
                    }

                    if (!occupied && count_neighbour == 0)
                    {
                        ferry_temp.write(x, y, '#');
                        changed = true;
                    }
                }
            }

            std::swap(ferry, ferry_temp);
        }

        return ferry.countAll('#');
    }

public:
    Day11()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_11.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_11.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
                                
        int64_t result_1 = runFerry(4, 1);
        int64_t result_2 = runFerry(5, std::numeric_limits<int32_t>::max());
        
        int64_t time = myTime.usPassed();
        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY11
