#ifndef ADVENTOFCODE2017_DAY11
#define ADVENTOFCODE2017_DAY11

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

class Day11 {
private:
	std::string inputString;

    std::string increment(std::string input)
    {
        std::string result = input;

        // Shortcut for i o l
        for (int8_t index = 0; index < 8; ++index)
        {
            if (result[index] == 'i' || result[index] == 'o' || result[index] == 'l')
            {
                result[index]++;
                for (int8_t subIdx = index + 1; subIdx < 8; ++subIdx)
                {
                    result[subIdx] = 'a';
                }

                return result;
            }
        }
        
        for (int8_t index = 7; index >= 0; --index)
        {
            if (result[index] == 'z')
            {
                result[index] = 'a';
            }
            else
            {
                result[index]++;
                break;
            }
        }

        return result;
    }

    bool checkValid(std::string password)
    {
        // Rule 1
        bool foundTriple = false;
        for (int8_t index = 0; index < 6 && !foundTriple; ++index)
        {
            auto a = password[index + 0];
            auto b = password[index + 1];
            auto c = password[index + 2];

            if ((a + 1 == b) && (b + 1 == c))
                foundTriple = true;
        }

        if (!foundTriple)
            return false;

        // Rule 2
        if (password.find('i') != std::string::npos ||
            password.find('o') != std::string::npos ||
            password.find('l') != std::string::npos)
            return false;

        // Rule 3
        bool foundFirstDouble = false;
        int8_t firstDouble = '0';
        for (int8_t index = 0; index < 7; ++index)
        {
            if (password[index] == password[index + 1] && password[index] != firstDouble)
            {
                if (foundFirstDouble)
                    return true;

                foundFirstDouble = true;
                firstDouble = password[index];
                index++;
            }
        }

        return false;
    }

    std::string part1()
    {
        std::string current = increment(inputString);

        while (!checkValid(current))
        {
            current = increment(current);
        }

        return current;
    }

    std::string part2(std::string start)
    {
        std::string current = increment(start);

        while (!checkValid(current))
        {
            current = increment(current);
        }

        return current;
    }

public:
	Day11()
	{
		inputString = util::readFile("..\\inputs\\2017\\input_11.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2(result_1);
        
        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY11