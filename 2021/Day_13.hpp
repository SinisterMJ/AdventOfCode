#ifndef ADVENTOFCODE2021_DAY13
#define ADVENTOFCODE2021_DAY13

#include "../includes/aoc.h"


class Day13 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::map<v2, int8_t> dots;
    std::vector<std::string> folds;

    std::map<v2, int8_t> fold_map(std::map<v2, int8_t> input, std::string task)
    {
        auto axis = task.substr(0, 1);
        auto position = std::stoi(task.substr(2));

        std::map<v2, int8_t> result;

        auto max_x = 0;
        auto max_y = 0;

        for (auto [pos, val] : input)
        {
            max_x = std::max(max_x, pos.x);
            max_y = std::max(max_y, pos.y);
        }

        if (axis == "x")
        {
            for (auto ind = position - 1; ind >= 0; --ind)
            {
                for (auto y = 0; y <= max_y; ++y)
                {
                    v2 pos = v2(ind, y);
                    result[pos] = input[pos];
                }
            }

            for (auto offset = 1; offset + position <= max_x; ++offset)
            {
                for (auto y = 0; y <= max_y; ++y)
                {
                    v2 pos = v2(offset + position, y);
                    if (input[pos] == '#')
                        result[v2(position - offset, y)] = input[pos];
                }
            }
        }

        if (axis == "y")
        {
            for (auto ind = position - 1; ind >= 0; --ind)
            {
                for (auto x = 0; x <= max_x; ++x)
                {
                    v2 pos = v2(x, ind);
                    result[pos] = input[pos];
                }
            }

            for (auto offset = 1; offset + position <= max_y; ++offset)
            {
                for (auto x = 0; x <= max_x; ++x)
                {
                    v2 pos = v2(x, offset + position);
                    if (input[pos] == '#')
                        result[v2(x, position - offset)] = input[pos];
                }
            }
        }

        return result;
    }

    int64_t part1()
    {

        for (auto ln : inputVec)
        {
            if (ln.find("fold") != std::string::npos)
            {
                folds.push_back(ln);
            }
            else
            {
                auto positions = util::splitInt(ln, ',');
                dots[v2(positions[0], positions[1])] = '#';
            }
        }

        std::string instruction = folds[0].substr(std::string("fold along ").size());

        auto result = fold_map(dots, instruction);

        int sum = 0;
        for (auto [pos, val] : result)
        {
            if (val == '#')
                sum++;
        }

        return sum;
    }

    std::string part2()
    {
        std::vector<std::string> folds;

        for (auto ln : inputVec)
        {
            if (ln.find("fold") != std::string::npos)
            {
                folds.push_back(ln);
            }
            else
            {
                auto positions = util::splitInt(ln, ',');
                dots[v2(positions[0], positions[1])] = '#';
            }
        }

        std::string result = "";
        std::map<v2, int8_t> input = dots;

        for (auto ln : folds)
        {
            std::string instruction = ln.substr(std::string("fold along ").size());
            input = fold_map(input, instruction);
        }

        int max_x = 0;
        int max_y = 0;

        for (auto [pos, val] : input)
        {
            max_x = std::max(max_x, pos.x);
            max_y = std::max(max_y, pos.y);
        }

        for (int y = 0; y <= max_y; ++y)
        {
            result += "\n";

            for (int x = 0; x <= max_x; ++x)
            {
                if (input[v2(x, y)] == 0)
                    result += " ";
                else
                    result += "#";
            }
        }

        return result;
    }

public:
    Day13()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_13.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_13.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
