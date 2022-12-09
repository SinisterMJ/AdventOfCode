#ifndef ADVENTOFCODE2022_DAY09
#define ADVENTOFCODE2022_DAY09

#include "../includes/aoc.h"

class Day09 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    v2 new_position(v2 head, v2 curr)
    {
        // They are touching
        if (std::abs(head.x - curr.x) <= 1 && std::abs(head.y - curr.y) <= 1)
            return curr;

        if (std::abs(head.x - curr.x) > 0)
            curr.x += sgn(head.x - curr.x);

        if (std::abs(head.y - curr.y) > 0)
            curr.y += sgn(head.y - curr.y);

        return curr;
    }

    int64_t part1()
    {
        v2 head(0, 0);
        v2 tail(0, 0);
        std::set<v2> tailPositions;
        tailPositions.insert(tail);

        for (auto line : inputVector)
        {
            auto moves = util::split(line, ' ');

            v2 dir(0, 0);

            if (moves[0] == "R")
                dir = v2(1, 0);
            if (moves[0] == "L")
                dir = v2(-1, 0);
            if (moves[0] == "U")
                dir = v2(0, 1);
            if (moves[0] == "D")
                dir = v2(0, -1);

            for (int index = 0; index < std::stoi(moves[1]); ++index)
            {
                head += dir;
                tail = new_position(head, tail);
                tailPositions.insert(tail);
            }
        }

        return tailPositions.size();
    }


    int64_t part2()
    {
        std::array<v2, 10> tails;
        
        std::set<v2> tailPositions;
        tailPositions.insert(v2(0, 0));

        for (auto line : inputVector)
        {
            auto moves = util::split(line, ' ');

            v2 dir(0, 0);

            if (moves[0] == "R")
                dir = v2(1, 0);
            if (moves[0] == "L")
                dir = v2(-1, 0);
            if (moves[0] == "U")
                dir = v2(0, 1);
            if (moves[0] == "D")
                dir = v2(0, -1);

            for (int index = 0; index < std::stoi(moves[1]); ++index)
            {
                tails[0] += dir;

                for (int i = 1; i < 10; ++i)
                {
                    tails[i] = new_position(tails[i - 1], tails[i]);
                }

                tailPositions.insert(tails[9]);
            }
        }

        return tailPositions.size();
    }
public:
    Day09()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_9.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY09