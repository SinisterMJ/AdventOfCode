#ifndef ADVENTOFCODE2016_DAY09
#define ADVENTOFCODE2016_DAY09

#include "../includes/aoc.h"
#include <map>
#include <tuple>

class Day09 {
private:
    std::string input;

    int64_t part1()
    {
        std::string decompressed{""};
        std::string remainder = input;
        //remainder = "X(8x2)(3x3)ABCY";

        while (true)
        {
            auto pos_open = remainder.find('(');
            auto pos_close = remainder.find(')');

            if (pos_open == std::string::npos)
            {
                decompressed += remainder;
                break;
            }

            std::string pre_string = remainder.substr(0, pos_open);

            std::string sNumbers = remainder.substr(pos_open + 1, pos_close - pos_open - 1);
            auto nums = util::splitInt(sNumbers, 'x');

            std::string pos_string = remainder.substr(pos_close + 1, nums[0]);

            decompressed += pre_string;

            for (int i = 0; i < nums[1]; ++i)
                decompressed += pos_string;

            remainder = remainder.substr(pos_close + 1 + nums[0]);
        }

        return decompressed.size();
    }

    int64_t getSubstringLength(std::string input)
    {
        int64_t result = 0;
        
        {
            auto pos_open = input.find('(');
            auto pos_close = input.find(')');

            if (pos_open == std::string::npos)
                return input.size();

            result += pos_open;

            std::string sNumbers = input.substr(pos_open + 1, pos_close - pos_open - 1);
            auto nums = util::splitInt(sNumbers, 'x');

            std::string pos_string = input.substr(pos_close + 1, nums[0]);

            result += getSubstringLength(pos_string) * nums[1];
            result += getSubstringLength(input.substr(pos_close + 1 + nums[0]));
        }

        return result;
    }

    int64_t part2()
    {
        return getSubstringLength(input);        
    }

public:
	Day09()
	{
        input = util::readFile("..\\inputs\\2016\\input_9.txt");
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

#endif  // ADVENTOFCODE2016_DAY09