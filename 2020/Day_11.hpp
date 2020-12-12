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
        std::vector<std::string> ferry_s = inputVec;
        std::vector<std::string> ferry_s_temp;
        std::vector<v2> neighbours = Map2DBase<int8_t>::getNeighboursVec(true);

        do 
        {
            ferry_s_temp = ferry_s;
            for (int y = 0; y < ferry_s_temp.size(); ++y)
            {
                for (int x = 0; x < ferry_s_temp[y].size(); ++x)
                {
                    if (ferry_s[y][x] == '.')
                        continue;
                    
                    bool occupied = (ferry_s_temp[y][x] == '#');
                    v2 pos(x, y);
                    int32_t count_neighbour = 0;

                    for (auto& elem : neighbours)
                    {
                        for (int index = 1; index <= max_vector; ++index)
                        {
                            v2 pos_neighbour = pos + elem * index;
                            if (in_range<int32_t>(pos_neighbour.x, 0, static_cast<int32_t>(ferry_s_temp[y].size()) - 1) &&
                                in_range<int32_t>(pos_neighbour.y, 0, static_cast<int32_t>(ferry_s_temp.size()) - 1))
                            {
                                if (ferry_s_temp[pos_neighbour.y][pos_neighbour.x] != '.')
                                {
                                    count_neighbour += (ferry_s_temp[pos_neighbour.y][pos_neighbour.x] == '#');
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
                        ferry_s[y][x] = 'L';
                    }

                    if (!occupied && count_neighbour == 0)
                    {
                        ferry_s[y][x] = '#';
                    }
                }
            }
        } while (ferry_s != ferry_s_temp);

        int32_t total = std::accumulate(std::begin(ferry_s), std::end(ferry_s), 0, [](int total, const auto& row) {
            return total + static_cast<int32_t>(std::count(std::begin(row), std::end(row), '#'));
        });

        return total;
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
