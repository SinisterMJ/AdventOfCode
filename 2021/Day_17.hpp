#ifndef ADVENTOFCODE2021_DAY17
#define ADVENTOFCODE2021_DAY17

#include "../includes/aoc.h"

class Day17 {
private:
    std::string inputString;

    int32_t target_x[2];
    int32_t target_y[2];

    int64_t part1()
    {
        auto pos_start = inputString.find("x") + 2;
        auto pos_end = inputString.find(",");
        std::string x_range = inputString.substr(pos_start, pos_end - pos_start);

        pos_start = x_range.find("..");
        target_x[0] = std::stoi(x_range.substr(0, pos_start));
        target_x[1] = std::stoi(x_range.substr(pos_start + 2));

        pos_start = inputString.find("y") + 2;
        std::string y_range = inputString.substr(pos_start);

        pos_start = y_range.find("..");
        target_y[0] = std::stoi(y_range.substr(0, pos_start));
        target_y[1] = std::stoi(y_range.substr(pos_start + 2));

        return target_y[0] * (target_y[0] + 1) / 2;
    }

    int64_t part2()
    {
        int32_t total_hits = 0;

        for (int x = 1; x <= target_x[1]; ++x)
        {
            for (int y = target_y[0]; y < -target_y[0]; ++y)
            {
                v2 position = v2(0, 0);
                v2 vector(x, y);

                while (position.y >= target_y[0] &&
                    position.x <= target_x[1] && // overshot target
                    (position.x >= target_x[0] || vector.x > 0)) // undershot target
                {
                    position += vector;
                    vector.x = std::max(0, vector.x - 1);
                    vector.y--;

                    if (target_x[0] <= position.x && position.x <= target_x[1] &&
                        target_y[0] <= position.y && position.y <= target_y[1])
                    {
                        total_hits++;
                        break;
                    }
                }
            }
        }

        return total_hits;
    }

public:
    Day17()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_17.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 17 - Part 1: " << result_1 << '\n'
            << "Day 17 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
