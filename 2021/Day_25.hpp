#ifndef ADVENTOFCODE2021_DAY25
#define ADVENTOFCODE2021_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int32_t part1()
    {
        std::vector<std::vector<int8_t>> seafloor;

        for (auto ln : inputVec)
        {
            std::vector<int8_t> row;
            for (auto ch : ln)
                row.emplace_back(ch);
            seafloor.emplace_back(row);
        }
                
        int steps = 0;
        while (true)
        {
            bool moved = false;

            std::vector<std::vector<int8_t>> after = seafloor;

            // print seafloor
            /*for (int y = 0; y < seafloor.size(); ++y)
            {
                for (int x = 0; x < seafloor[y].size(); ++x)
                {
                    std::cout << seafloor[y][x];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;*/

            for (int y = 0; y < seafloor.size(); ++y)
            {
                for (int x = 0; x < seafloor[y].size(); ++x)
                {
                    if (seafloor[y][x] == '>')
                    {
                        if (seafloor[y][(x + 1) % seafloor[y].size()] == '.')
                        {
                            after[y][x] = '.';
                            after[y][(x + 1) % seafloor[y].size()] = '>';
                            moved = true;
                        }
                    }
                }
            }

            std::swap(after, seafloor);
            after = seafloor;

            for (int y = 0; y < seafloor.size(); ++y)
            {
                for (int x = 0; x < seafloor[y].size(); ++x)
                {
                    if (seafloor[y][x] == 'v')
                    {
                        if (seafloor[(y + 1) % seafloor.size()][x] == '.')
                        {
                            after[y][x] = '.';
                            after[(y + 1) % seafloor.size()][x] = 'v';
                            moved = true;
                        }
                    }
                }
            }

            std::swap(seafloor, after);

            steps++;

            if (!moved)
                return steps;
        }

        return 0;
    }

public:
    Day25()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_25.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_25.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();

        int64_t time = myTime.usPassed();
        std::cout << "Day 25 - Part 1: " << result_1 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY25
