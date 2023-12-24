#ifndef ADVENTOFCODE2023_DAY24
#define ADVENTOFCODE2023_DAY24

#include "../includes/aoc.h"
#include <algorithm>

class Day24 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Hail {
        v3 position;
        v3 velocity;
    };

    std::vector<Hail> crystals;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            auto info = util::split(line, " @ ");
            auto pos = util::splitInt64(info[0], ',');
            auto vel = util::splitInt64(info[1], ',');

            Hail temp;
            temp.position = v3(pos[0], pos[1], pos[2]);
            temp.velocity = v3(vel[0], vel[1], vel[2]);

            crystals.push_back(temp);
        }

        int32_t intersections{ 0 };

        for (int i = 0; i < crystals.size(); ++i)
        {
            for (int j = i + 1; j < crystals.size(); ++j)
            {
                Hail pos_1 = crystals[i];
                Hail pos_2 = crystals[j];
                
                int64_t c1 = pos_2.position.x - pos_1.position.x;
                int64_t c2 = pos_2.position.y - pos_1.position.y;
                int64_t b1 = -pos_2.velocity.x;
                int64_t b2 = -pos_2.velocity.y;
                int64_t a1 = pos_1.velocity.x;
                int64_t a2 = pos_1.velocity.y;

                double a = (c1 * b2 - b1 * c2) / static_cast<double>(a1 * b2 - b1 * a2);
                double b = (a1 * c2 - c1 * a2) / static_cast<double>(a1 * b2 - b1 * a2);

                if (a < 0 || b < 0)
                    continue;

                double cross_x = pos_1.position.x + a * pos_1.velocity.x;
                double cross_y = pos_1.position.y + a * pos_1.velocity.y;

                bool in_area = in_range<double>(cross_x, 200000000000000, 400000000000000);
                in_area &= in_range<double>(cross_y, 200000000000000, 400000000000000);

                //in_area = in_range<double>(cross_x, 7, 27);
                //in_area &= in_range<double>(cross_y, 7, 27);

                intersections += in_area;
            }
        }

        return intersections;
    }

    int64_t part2()
    {
        // Solved with Z3...

        /*
        from z3 import *

        rx, ry, rz = Ints('rx ry rz')
        rvx, rvy, rvz = Ints('rvx rvy rvz')
        t0, t1, t2 = Ints('t0 t1 t2')
        answer = Int('answer')

        solve(
            rx + t0 * rvx == 200027938836082 + t0 * 133,
            ry + t0 * rvy == 135313515251542 + t0 * 259,
            rz + t0 * rvz == 37945458137479 + t0 * 506,

            rx + t1 * rvx == 285259862606823 + t1 * 12,
            ry + t1 * rvy == 407476720802151 + t1 * -120,
            rz + t1 * rvz == 448972585175416 + t1 * -241,

            rx + t2 * rvx == 329601664688534 + t2 * -133,
            ry + t2 * rvy == 370686722303193 + t2 * -222,
            rz + t2 * rvz == 178908568819244 + t2 * 168,

            answer == rx + ry + rz,
        )
        */
        return 546494494317645;
    }

public:
    Day24()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_24.txt");
        inputString = util::readFile("..\\inputs\\2023\\input_24.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 24 - Part 1: " << result_1 << '\n'
                  << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY24