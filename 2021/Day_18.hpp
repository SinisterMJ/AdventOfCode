#ifndef ADVENTOFCODE2021_DAY18
#define ADVENTOFCODE2021_DAY18

#include "../includes/aoc.h"
#include <functional>

class Day18 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    
    int64_t parseBracesRec(std::string partialMath, std::function<int64_t(std::string)> recurse) 
    {
        while (partialMath.find("(") != std::string::npos)
        {
            auto posClose = partialMath.find(")");
            auto posOpen = partialMath.rfind("(", posClose);

            std::string sub = partialMath.substr(posOpen + 1, posClose - posOpen - 1);

            int64_t resultInner = parseBracesRec(sub, recurse);
            partialMath.replace(posOpen, sub.size() + 2, std::to_string(resultInner));
        }

        return recurse(partialMath);
    }
        
    int64_t part1_math(std::string partialMath)
    {
        auto vec = util::split(partialMath, ' ');
        int64_t result = std::stoll(vec[0]);

        for (int index = 1; index < vec.size(); index += 2)
        {
            int64_t op = std::stoll(vec[index + 1]);
            if (vec[index] == "*")
            {
                result *= op;
            }
            else
            {
                result += op;
            }
        }

        return result;
    }

    int64_t part2_math(std::string partialMath)
    {
        auto vec = util::split(partialMath, ' ');
        int64_t result = 1;

        for (int index = 1; index < vec.size(); index += 2)
        {
            if (vec[index] == "+")
            {
                int64_t temp = std::stoll(vec[index - 1]) + std::stoll(vec[index + 1]);
                vec.erase(vec.begin() + index - 1, vec.begin() + index + 1);
                vec[index - 1] = std::to_string(temp);
                index -= 2;
            }
        }

        for (int index = 0; index < vec.size(); index += 2)
        {
            result *= std::stoll(vec[index]);
        }

        return result;
    }

public:
    Day18()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_18.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_18.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        int64_t result_1 = 0;
        int64_t result_2 = 0;

        for (auto line : inputVec)
        {
            result_1 += parseBracesRec(line, [this](std::string math) { return part1_math(math); });
            result_2 += parseBracesRec(line, [this](std::string math) { return part2_math(math); });
        }

        int64_t time = myTime.usPassed();
        std::cout << "Day 18 - Part 1: " << result_1 << '\n'
                  << "Day 18 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY18
