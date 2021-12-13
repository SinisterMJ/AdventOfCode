#ifndef ADVENTOFCODE2021_DAY13
#define ADVENTOFCODE2021_DAY13

#include "../includes/aoc.h"
#include <set>

class Day13 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::set<v2> dots;
    std::vector<std::string> folds;

    std::set<v2> fold_map(std::set<v2> input, std::string task)
    {
        auto axis = task.substr(0, 1);
        auto position = std::stoi(task.substr(2));

        std::set<v2> result;

        if (axis == "x")
        {
            for (auto element : input)
            {
                if (element.x < position)
                {
                    result.insert(element);
                }
                else
                {
                    if (element.x == position)
                    {
                        continue;
                    }
                    int offset = element.x - position;
                    result.insert(v2(position - offset, element.y));
                }
            }
        }

        if (axis == "y")
        {
            for (auto element : input)
            {
                if (element.y < position)
                {
                    result.insert(element);
                }
                else
                {
                    if (element.y == position)
                    {
                        continue;
                    }
                    int offset = element.y - position;
                    result.insert(v2(element.x, position - offset));
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
                dots.insert(v2(positions[0], positions[1]));
            }
        }

        std::string instruction = folds[0].substr(std::string("fold along ").size());

        auto result = fold_map(dots, instruction);
        return result.size();
    }

    std::string part2()
    {
        std::string result = "";
        std::set<v2> input = dots;

        for (auto ln : folds)
        {
            std::string instruction = ln.substr(std::string("fold along ").size());
            input = fold_map(input, instruction);
        }

        int max_x = 0;
        int max_y = 0;

        for (auto pos : input)
        {
            max_x = std::max(max_x, pos.x);
            max_y = std::max(max_y, pos.y);
        }

        for (int y = 0; y <= max_y; ++y)
        {
            result += "\n";

            for (int x = 0; x <= max_x; ++x)
            {
                if (input.find(v2(x, y)) == input.end())
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
