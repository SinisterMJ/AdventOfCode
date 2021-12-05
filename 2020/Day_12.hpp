#ifndef ADVENTOFCODE2020_DAY12
#define ADVENTOFCODE2020_DAY12

#include "../includes/aoc.h"

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        v2 east(1, 0);
        v2 west(-1, 0);
        v2 north(0, 1);
        v2 south(0, -1);

        v2 curDir = east;
        v2 curPos(0, 0);

        for (auto elem : inputVec)
        {
            int8_t direction = elem[0];
            int value = std::stoi(elem.substr(1));

            if (direction == 'N')
                curPos += north * value;

            if (direction == 'S')
                curPos += south * value;

            if (direction == 'E')
                curPos += east * value;

            if (direction == 'W')
                curPos += west * value;

            if (direction == 'F')
                curPos += curDir * value;

            if (direction == 'R' || direction == 'L')
            {
                bool clockwise = (direction == 'R');
                if (!clockwise)
                {
                    value = 360 - value;
                }

                if (value == 90)
                {
                    v2 temp = curDir;
                    curDir.x = temp.y;
                    curDir.y = -temp.x;
                }

                if (value == 180)
                {
                    v2 temp = curDir;
                    curDir.x = -temp.x;
                    curDir.y = -temp.y;
                }

                if (value == 270)
                {
                    v2 temp = curDir;
                    curDir.x = -temp.y;
                    curDir.y = temp.x;
                }
            }
        }

        return abs(curPos.x) + abs(curPos.y);
    }

    int64_t part2()
    {
        v2 east(1, 0);
        v2 west(-1, 0);
        v2 north(0, 1);
        v2 south(0, -1);

        v2 curDir(10, 1);
        v2 curPos(0, 0);

        for (auto elem : inputVec)
        {
            int8_t direction = elem[0];
            int value = std::stoi(elem.substr(1));

            if (direction == 'N')
                curDir += north * value;

            if (direction == 'S')
                curDir += south * value;

            if (direction == 'E')
                curDir += east * value;

            if (direction == 'W')
                curDir += west * value;

            if (direction == 'F')
                curPos += curDir * value;

            if (direction == 'R' || direction == 'L')
            {
                bool clockwise = (direction == 'R');
                if (!clockwise)
                {
                    value = 360 - value;
                }

                if (value == 90)
                {
                    v2 temp = curDir;
                    curDir.x = temp.y;
                    curDir.y = -temp.x;
                }

                if (value == 180)
                {
                    v2 temp = curDir;
                    curDir.x = -temp.x;
                    curDir.y = -temp.y;
                }

                if (value == 270)
                {
                    v2 temp = curDir;
                    curDir.x = -temp.y;
                    curDir.y = temp.x;
                }
            }
        }

        return abs(curPos.x) + abs(curPos.y);
    }

public:
    Day12()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_12.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_12.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY12
