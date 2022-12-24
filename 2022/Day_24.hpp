#ifndef ADVENTOFCODE2022_DAY24
#define ADVENTOFCODE2022_DAY24

#include "../includes/aoc.h"

class Day24 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<v2, int8_t> expedition;
    std::vector<v2> blizzard_down;
    std::vector<v2> blizzard_up;
    std::vector<v2> blizzard_right;
    std::vector<v2> blizzard_left;

    int max_y = 0;
    int max_x = 0;

    int solve(v2 start, v2 end)
    {
        int step = 0;
        std::set<v2> positions;
        positions.insert(start);
        while (true)
        {
            // Move all blizzards first
            std::set<v2> blizzards;
            std::set<v2> new_positions;

            for (auto& el : blizzard_down)
            {
                el += v2(0, 1);
                if (el.y == max_y)
                    el.y = 1;
                blizzards.insert(el);
            }

            for (auto& el : blizzard_up)
            {
                el += v2(0, -1);
                if (el.y == 0)
                    el.y = max_y - 1;
                blizzards.insert(el);
            }

            for (auto& el : blizzard_left)
            {
                el += v2(-1, 0);
                if (el.x == 0)
                    el.x = max_x - 1;
                blizzards.insert(el);
            }

            for (auto& el : blizzard_right)
            {
                el += v2(1, 0);
                if (el.x == max_x)
                    el.x = 1;
                blizzards.insert(el);
            }

            for (auto pos : positions)
            {
                if (!blizzards.contains(pos + v2(0, 1)) && expedition.contains(pos + v2(0, 1)) && expedition[pos + v2(0, 1)] != '#')
                    new_positions.insert(pos + v2(0, 1));
                if (!blizzards.contains(pos + v2(0, -1)) && expedition.contains(pos + v2(0, -1)) && expedition[pos + v2(0, -1)] != '#')
                    new_positions.insert(pos + v2(0, -1));
                if (!blizzards.contains(pos + v2(1, 0)) && expedition.contains(pos + v2(1, 0)) && expedition[pos + v2(1, 0)] != '#')
                    new_positions.insert(pos + v2(1, 0));
                if (!blizzards.contains(pos + v2(-1, 0)) && expedition.contains(pos + v2(-1, 0)) && expedition[pos + v2(-1, 0)] != '#')
                    new_positions.insert(pos + v2(-1, 0));
                if (!blizzards.contains(pos))
                    new_positions.insert(pos);
            }

            step++;

            std::swap(positions, new_positions);
            
            if (positions.contains(end))
                return step;
        }
    }

    std::pair<int, int> solver()
    {
        for (auto line : inputVector)
        {
            int x = 0;
            for (auto ch : line)
            {
                expedition[v2(x, max_y)] = ch;

                if (ch == '<')
                    blizzard_left.emplace_back(x, max_y);
                if (ch == '>')
                    blizzard_right.emplace_back(x, max_y);
                if (ch == 'v')
                    blizzard_down.emplace_back(x, max_y);
                if (ch == '^')
                    blizzard_up.emplace_back(x, max_y);
                ++x;
            }

            max_x = x - 1;
            max_y++;
        }

        max_y--;

        std::set<v2> blizzards;

        v2 start(0, 0);
        for (; expedition[start] == '#'; start.x++);
        v2 end(0, max_y);
        for (; expedition[end] == '#'; end.x++);

        int first = solve(start, end);
        int second = solve(end, start);
        int third = solve(start, end);


        return std::make_pair(first, first + second + third);
    }

public:
    Day24()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_24.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_24.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solver();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 24 - Part 1: " << result_1 << '\n'
                  << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY24