#ifndef ADVENTOFCODE2022_DAY22
#define ADVENTOFCODE2022_DAY22

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day22 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        bool map = true;
        int y = 0;
        std::string instructions = "";

        Map2DBase<int8_t> jungle('.');
        for (auto line : inputVector)
        {
            if (line == "")
                map = false;

            if (map)
            {
                int x = 0;
                for (auto ch : line)
                {
                    if (ch != ' ')
                    {
                        jungle.write(v2(x, y), ch);
                    }
                    x++;
                }
                y++;
            }
            else
            {
                instructions = line;
            }
        }

        v2 pos(0, 0);
        for (int x = 0;; ++x)
        {
            if (jungle.validIndex(x, 0) && !jungle.checkOccupation(x, 0))
            {
                pos.x = x;
                break;
            }
        }

        v2 dir(1, 0);

        while (instructions.size() > 0)
        {
            int64_t nextL = instructions.find('L');
            int64_t nextR = instructions.find('R');

            if (nextL == std::string::npos)
                nextL = std::numeric_limits<int32_t>::max();
            if (nextR == std::string::npos)
                nextR = std::numeric_limits<int32_t>::max();

            int32_t steps = 0;
            if (nextL != nextR) // both max
                steps = std::stoi(instructions.substr(0, std::min(nextL, nextR)));
            else
                steps = std::stoi(instructions);

            instructions = instructions.substr(std::to_string(steps).size());

            for (int i = 0; i < steps; ++i)
            {
                v2 new_pos = pos + dir;
                if (jungle.validIndex(new_pos))
                {
                    if (jungle.read(new_pos) == '#')
                        break;
                    pos = new_pos;
                }
                else
                {
                    int j = 1;
                    for (; jungle.validIndex(new_pos - dir * j); ++j);
                    
                    new_pos = new_pos - dir * (j - 1);
                    if (jungle.read(new_pos) == '#')
                        break;
                    pos = new_pos;
                }
            }

            if (instructions.size() > 0)
            {
                if (instructions[0] == 'L')
                    dir = MapHelper::turnRight(dir);
                else
                    dir = MapHelper::turnLeft(dir);

                instructions = instructions.substr(1);
            }
        }

        int angleVal = 0;
        if (dir == v2(0, 1))
            angleVal = 1;
        if (dir == v2(-1, 0))
            angleVal = 2;
        if (dir == v2(0, -1))
            angleVal = 3;


        return (pos.y + 1) * 1000 + (pos.x + 1) * 4 + angleVal;
    }

    int64_t part2()
    {
        int y = 0;
        std::string instructions = "";
        std::map<v3, int8_t> cube;

        v3 pos(0, 0, 0);
        for (auto line : inputVector)
        {
            if (line == "")
                break;
            int x = 0;

            for (auto ch : line)
            {
                if (ch != ' ')
                {
                    pos.x = x % 50;
                    pos.y = y % 50;

                    // Hardcode the side mapping
                    if (in_range(x, 50, 99) && in_range(y, 0, 49))
                        pos.z = 1;
                    if (in_range(x, 100, 149) && in_range(y, 0, 49))
                        pos.z = 2;
                    if (in_range(x, 50, 99) && in_range(y, 50, 99))
                        pos.z = 3;
                    if (in_range(x, 50, 99) && in_range(y, 100, 149))
                        pos.z = 4;
                    if (in_range(x, 0, 49) && in_range(y, 100, 149))
                        pos.z = 5;
                    if (in_range(x, 0, 49) && in_range(y, 150, 199))
                        pos.z = 6;

                    cube[pos] = ch;
                }
                x++;
            }
            y++;
        }
        
        instructions = inputVector.at(inputVector.size() - 1);

        pos = v3(0, 0, 1);
        for (;; pos.x++)
            if (cube[pos] == '.')
                break;

        v2 dir(1, 0);

        while (instructions.size() > 0)
        {
            int64_t nextL = instructions.find('L');
            int64_t nextR = instructions.find('R');

            if (nextL == std::string::npos)
                nextL = std::numeric_limits<int32_t>::max();
            if (nextR == std::string::npos)
                nextR = std::numeric_limits<int32_t>::max();

            int32_t steps = 0;
            if (nextL != nextR) // both max
                steps = std::stoi(instructions.substr(0, std::min(nextL, nextR)));
            else
                steps = std::stoi(instructions);

            for (int i = 0; i < steps; ++i)
            {
                v3 new_pos = pos;
                new_pos.x += dir.x;
                new_pos.y += dir.y;
                v2 new_dir = dir;
                if (cube.contains(new_pos))
                {
                    if (cube[new_pos] == '#')
                        break;
                    pos = new_pos;
                }
                else
                {
                    if (new_pos.x == 50) // walked out the right side
                    {
                        if (pos.z == 1) // First side, walk into 2, with no changes to direction / position
                        {
                            new_pos.z = 2;
                            new_pos.x = 0;
                        }
                        else if (pos.z == 2) // Second side, walk into 4. Change direction by 180. Flip Y
                        {
                            new_pos.z = 4;
                            new_pos.x = 49;
                            new_pos.y = 49 - new_pos.y;
                            new_dir = v2(-1, 0);
                        }
                        else if (pos.z == 3) // Third side, walk into 2. Change direction by 90 Left
                        {
                            new_pos.z = 2;
                            new_pos.x = new_pos.y;
                            new_pos.y = 49;
                            new_dir = v2(0, -1);
                        }
                        else if (pos.z == 4) // Fourth side, walk into 2. Change direction by 180. Flip Y
                        {
                            new_pos.z = 2;
                            new_pos.x = 49;
                            new_pos.y = 49 - new_pos.y;
                            new_dir = v2(-1, 0);
                        }
                        else if (pos.z == 5) // Fifth side, walk into 4, with no changes to direction / position
                        {
                            new_pos.z = 4;
                            new_pos.x = 0;
                        }
                        else if (pos.z == 6) // Sixth side, walk into 4, Change direction 90 left
                        {
                            new_pos.z = 4;
                            new_pos.x = new_pos.y;
                            new_pos.y = 49;
                            new_dir = v2(0, -1);
                        }
                    }
                    if (new_pos.x == -1) // walked out the left side
                    {
                        if (pos.z == 1) // First side, walk into 5, flip 180
                        {
                            new_pos.z = 5;
                            new_pos.x = 0;
                            new_pos.y = 49 - new_pos.y;
                            new_dir = v2(1, 0);
                        }
                        else if (pos.z == 2) // Second side, walk into 1. 
                        {
                            new_pos.z = 1;
                            new_pos.x = 49;
                        }
                        else if (pos.z == 3) // Third side, walk into 5. Change direction by 90 Left
                        {
                            new_pos.z = 5;
                            new_pos.x = new_pos.y;
                            new_pos.y = 0;
                            new_dir = v2(0, 1);
                        }
                        else if (pos.z == 4) // Fourth side, walk into 5.
                        {
                            new_pos.z = 5;
                            new_pos.x = 49;
                        }
                        else if (pos.z == 5) // Fifth side, walk into 1, flip 180
                        {
                            new_pos.z = 1;
                            new_pos.x = 0;
                            new_pos.y = 49 - new_pos.y;
                            new_dir = v2(1, 0);
                        }
                        else if (pos.z == 6) // Sixth side, walk into 1, Change direction 90 left
                        {
                            new_pos.z = 1;
                            new_pos.x = new_pos.y;
                            new_pos.y = 0;
                            new_dir = v2(0, 1);
                        }
                    }

                    if (new_pos.y == -1) // walked out the top side
                    {
                        if (pos.z == 1) // First side, walk into 6, turn 90 right
                        {
                            new_pos.z = 6;
                            new_pos.y = new_pos.x;
                            new_pos.x = 0;
                            new_dir = v2(1, 0);
                        }
                        else if (pos.z == 2) // Second side, walk into 6. 
                        {
                            new_pos.z = 6;
                            new_pos.y = 49;
                        }
                        else if (pos.z == 3) // Third side, walk into 1.
                        {
                            new_pos.z = 1;
                            new_pos.y = 49;
                        }
                        else if (pos.z == 4) // Fourth side, walk into 3.
                        {
                            new_pos.z = 3;
                            new_pos.y = 49;
                        }
                        else if (pos.z == 5) // Fifth side, walk into 1, right by 90
                        {
                            new_pos.z = 3;
                            new_pos.y = new_pos.x;
                            new_pos.x = 0;
                            new_dir = v2(1, 0);
                        }
                        else if (pos.z == 6) // Sixth side, walk into 5.
                        {
                            new_pos.z = 5;
                            new_pos.y = 49;
                        }
                    }

                    if (new_pos.y == 50) // walked out the bottom side
                    {
                        if (pos.z == 1) // First side, walk into 3.
                        {
                            new_pos.z = 3;
                            new_pos.y = 0;
                        }
                        else if (pos.z == 2) // Second side, walk into 3. Turn left 90
                        {
                            new_pos.z = 3;
                            new_pos.y = new_pos.x;
                            new_pos.x = 49;
                            new_dir = v2(-1, 0);
                        }
                        else if (pos.z == 3) // Third side, walk into 4.
                        {
                            new_pos.z = 4;
                            new_pos.y = 0;
                        }
                        else if (pos.z == 4) // Fourth side, walk into 6, turn left 90
                        {
                            new_pos.z = 6;
                            new_pos.y = new_pos.x;
                            new_pos.x = 49;
                            new_dir = v2(-1, 0);
                        }
                        else if (pos.z == 5) // Fifth side, walk into 6.
                        {
                            new_pos.z = 6;
                            new_pos.y = 0;
                        }
                        else if (pos.z == 6) // Sixth side, walk into 2.
                        {
                            new_pos.z = 2;
                            new_pos.y = 0;
                        }
                    }

                    if (cube[new_pos] == '#')
                        break;
                    pos = new_pos;
                    dir = new_dir;
                }
            }

            instructions = instructions.substr(std::to_string(steps).size());
                        
            if (instructions.size() > 0)
            {
                if (instructions[0] == 'L')
                    dir = MapHelper::turnRight(dir);
                else
                    dir = MapHelper::turnLeft(dir);

                instructions = instructions.substr(1);
            }
        }

        int angleVal = 0;
        if (dir == v2(0, 1))
            angleVal = 1;
        if (dir == v2(-1, 0))
            angleVal = 2;
        if (dir == v2(0, -1))
            angleVal = 3;

        v3 finalMapPos = pos;

        if (pos.z == 1)
        {
            finalMapPos.x += 50;
        }
        if (pos.z == 2)
        {
            finalMapPos.x += 100;
        }
        if (pos.z == 3)
        {
            finalMapPos.x += 50;
            finalMapPos.y += 50;
        }
        if (pos.z == 4)
        {
            finalMapPos.x += 50;
            finalMapPos.y += 100;
        }
        if (pos.z == 5)
        {
            finalMapPos.x += 0;
            finalMapPos.y += 100;
        }
        if (pos.z == 6)
        {
            finalMapPos.x += 0;
            finalMapPos.y += 150;
        }

        return (finalMapPos.y + 1) * 1000 + (finalMapPos.x + 1) * 4 + angleVal;
    }

public:
    Day22()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_22.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_22.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 22 - Part 1: " << result_1 << '\n'
                  << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY22