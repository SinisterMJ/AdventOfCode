#ifndef ADVENTOFCODE2023_DAY01
#define ADVENTOFCODE2023_DAY01

#include "../includes/aoc.h"
#include <algorithm>

class Day01 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::map<std::string, std::string> replacements;

    int64_t part1(bool replace)
    {
        replacements["one"] = "1";
        replacements["two"] = "2";
        replacements["three"] = "3";
        replacements["four"] = "4";
        replacements["five"] = "5";
        replacements["six"] = "6";
        replacements["seven"] = "7";
        replacements["eight"] = "8";
        replacements["nine"] = "9";
        int result = 0;
        for (auto line : inputVector)
        {
            if (replace)
            {
                std::string new_line = "";
                for (int index = 0; index < line.size(); ++index)
                {
                    bool replaced = false;
                    for (auto [before, after] : replacements)
                    {
                        if (line.substr(index, before.size()) == before)
                        {
                            new_line += after;
                            replaced = true;
                        }
                    }
                    if (!replaced)
                        new_line += line.substr(index, 1);
                }
                line = new_line;
            }

            for (int i = 0; i < line.length(); ++i)
            {
                if (in_range<char>(line[i], '0', '9'))
                { 
                    result += (line[i] - '0') * 10;
                    break;
                }
            }
            
            for (int64_t i = line.length() - 1; i >= 0; --i)
            {
                if (in_range<char>(line[i], '0', '9'))
                {
                    result += (line[i] - '0');
                    break;
                }
            }
        }

        return result;
    }

public:
    Day01()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_1.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result_1 = part1(false);
        auto result_2 = part1(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 01 - Part 1: " << result_1 << '\n'
                  << "Day 01 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY01