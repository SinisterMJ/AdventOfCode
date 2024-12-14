#ifndef ADVENTOFCODE2024_DAY14
#define ADVENTOFCODE2024_DAY14

#include "../includes/aoc.h"
#include <algorithm>

class Day14 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct robot {
        v2 pos;
        v2 speed;
    };


    int64_t part1()
    {
        std::vector<robot> robots;
        for (auto line : inputVector)
        {
            auto pos_speed = util::split(line, ' ');
            auto pos_ = util::split(pos_speed[0], '=');
            auto pos = util::split(pos_[1], ',');

            auto vec_ = util::split(pos_speed[1], '=');
            auto vec = util::split(vec_[1], ',');

            robot t;
            t.pos = v2(std::stoll(pos[0]), std::stoll(pos[1]));
            t.speed = v2(std::stoll(vec[0]), std::stoll(vec[1]));

            robots.push_back(t);
        }

        int width = 101;
        int height = 103;

        for (int i = 0; i < 100; ++i)
        {
            for (auto& rob : robots)
            {
                rob.pos += rob.speed;
                while (rob.pos.x < 0)
                    rob.pos.x += width;
                if (rob.pos.x >= width)
                    rob.pos.x = rob.pos.x % width;

                while (rob.pos.y < 0)
                    rob.pos.y += height;
                if (rob.pos.y >= height)
                    rob.pos.y = rob.pos.y % height;
            }
        }

        int64_t count_lt = 0;
        int64_t count_rt = 0;
        int64_t count_lb = 0;
        int64_t count_rb = 0;

        for (auto& rob : robots)
        {
            if (in_range<int64_t>(rob.pos.y, 0, height / 2 - 1) && in_range<int64_t>(rob.pos.x, 0, width / 2 - 1))
                count_lt++;
            if (in_range<int64_t>(rob.pos.y, 0, height / 2 - 1) && in_range<int64_t>(rob.pos.x, width / 2 + 1, width - 1))
                count_rt++;
            if (in_range<int64_t>(rob.pos.y, height / 2 + 1, height) && in_range<int64_t>(rob.pos.x, 0, width / 2 - 1))
                count_lb++;
            if (in_range<int64_t>(rob.pos.y, height / 2 + 1, height) && in_range<int64_t>(rob.pos.x, width / 2 + 1, width))
                count_rb++;
        }

        return count_lt * count_rt * count_lb * count_rb;
    }

    int64_t part2()
    {
        std::vector<robot> robots;
        for (auto line : inputVector)
        {
            auto pos_speed = util::split(line, ' ');
            auto pos_ = util::split(pos_speed[0], '=');
            auto pos = util::split(pos_[1], ',');

            auto vec_ = util::split(pos_speed[1], '=');
            auto vec = util::split(vec_[1], ',');

            robot t;
            t.pos = v2(std::stoll(pos[0]), std::stoll(pos[1]));
            t.speed = v2(std::stoll(vec[0]), std::stoll(vec[1]));

            robots.push_back(t);
        }

        int width = 101;
        int height = 103;

        int steps = 1;

        for (;;steps++)
        {
            std::set<v2> points;
            for (auto& rob : robots)
            {
                rob.pos += rob.speed;
                while (rob.pos.x < 0)
                    rob.pos.x += width;
                if (rob.pos.x >= width)
                    rob.pos.x = rob.pos.x % width;

                while (rob.pos.y < 0)
                    rob.pos.y += height;
                if (rob.pos.y >= height)
                    rob.pos.y = rob.pos.y % height;

                points.insert(rob.pos);
            }

            std::set<v2> positions;
            for (auto& pos : points)
                positions.insert(pos);

            if (positions.size() != robots.size())
                continue;

            return steps;

            //std::system("CLS");

            //std::cout << "Seconds passed: " << steps << std::endl;

            //for (int y = 0; y < height; ++y)
            //{
            //    for (int x = 0; x < width; ++x)
            //    {
            //        bool foundRob = false;
            //        for (auto& rob : robots)
            //        {
            //            if (rob.pos == v2(x, y))
            //                foundRob = true;
            //        }

            //        if (foundRob)
            //            std::cout << "*";
            //        else
            //            std::cout << " ";
            //    }
            //    std::cout << std::endl;
            //}            
        }
        
        return 0;
    }

public:
    Day14()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_14.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY14