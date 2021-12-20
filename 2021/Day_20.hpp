#ifndef ADVENTOFCODE2021_DAY20
#define ADVENTOFCODE2021_DAY20

#include "../includes/aoc.h"
#include <unordered_map>

class Day20 {
private:
        
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t solve(int iterations)
    {
        std::string codec = inputVec[0];
        std::unordered_map<v2, int8_t> image;

        v2 pos(0, 0);

        for (int index = 1; index < inputVec.size(); ++index)
        {
            pos.x = 0;
            auto ln = inputVec[index];
            for (auto ch : ln)
            {
                image[pos] = ch;
                pos.x++;
            }
            pos.y++;
        }

        std::vector<v2> neighbours;
        neighbours.emplace_back(-1, -1);
        neighbours.emplace_back(0, -1);
        neighbours.emplace_back(1, -1);

        neighbours.emplace_back(-1, 0);
        neighbours.emplace_back(0, 0);
        neighbours.emplace_back(1, 0);

        neighbours.emplace_back(-1, 1);
        neighbours.emplace_back(0, 1);
        neighbours.emplace_back(1, 1);

        std::unordered_map<v2, int8_t> swap;

        for (int i = 0; i < iterations; ++i)
        {
            int max_x = 0;
            int max_y = 0;
            int min_x = 0;
            int min_y = 0;

            for (auto [position, val] : image)
            {
                max_x = std::max(position.x, max_x);
                max_y = std::max(position.y, max_y);

                min_x = std::min(position.x, min_x);
                min_y = std::min(position.y, min_y);
            }

            for (int y = min_y - 2; y <= max_y + 2; ++y)
            {
                for (int x = min_x - 2; x <= max_x + 2; ++x)
                {
                    pos.x = x;
                    pos.y = y;

                    int16_t val = 0;

                    for (auto n : neighbours)
                    {
                        val *= 2;
                        if (image.find(pos + n) != image.end())
                        {
                            val += (image[pos + n] == '#');
                        }
                        else
                        {
                            val += (i % 2);  // This needs to be done because of the infinite background flipping dark / lit
                        }
                    }
                    swap[pos] = codec[val];
                }           
            }

            std::swap(swap, image);
            swap.clear();
        }

        int32_t sum = 0;

        for (auto [_, val] : image)
        {
            sum += (val == '#');
        }

        return sum;
    }

public:
    Day20()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_20.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_20.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
                
        auto result_1 = solve(2);
        auto result_2 = solve(50);

        int64_t time = myTime.usPassed();
        std::cout 
            << "Day 20 - Part 1: " << result_1 << '\n'
            << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY20
