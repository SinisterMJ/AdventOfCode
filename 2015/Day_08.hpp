#ifndef ADVENTOFCODE2015_DAY08
#define ADVENTOFCODE2015_DAY08

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day08 {
private:
	std::vector<std::string> inputVec;

    int32_t getCountBackslash(std::string input)
    {
        int count = 0;

        int64_t pos = 0;

        while ((pos = (input.find("\\\\", pos))) != std::string::npos)
        {
            pos += 2;
            count++;
        }

        return count;
    }

    int32_t getCountQuotes(std::string input)
    {
        int count = 0;

        int64_t pos = 0;

        while ((pos = (input.find("\\\"", pos))) != std::string::npos)
        {
            pos += 2;
            count++;
        }

        return count;
    }

    int32_t getCountHex(std::string input)
    {
        int count = 0;

        int64_t pos = 0;

        while ((pos = (input.find("\\x", pos))) != std::string::npos)
        {
            pos += 4;
            count++;
        }

        return count;
    }

    int64_t getLength(std::string input)
    {
        int64_t count = input.length() - 2;
        for (int index = 0; index < input.size(); ++index)
        {
            if (input[index] == '\\')
            {
                count--;
                index++;
                if (input[index] == 'x')
                {
                    count -= 2;
                    index += 2;
                }
            }
        }

        return count;
    }

    int64_t increaseLength(std::string input)
    {
        std::string result = "\"";
        result.reserve(input.size() * 2);
        for (int index = 0; index < input.size(); ++index)
        {
            if (input[index] == '\"' || input[index] == '\\')
            {
                result += "\\";
            }

            result += input[index];
        }

        result += "\"";

        return result.size();
    }

public:
	Day08()
	{
        inputVec = util::readFileLines("..\\inputs\\2015\\input_8.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        auto result_1 = 0;
        auto result_2 = 0;

        for (auto elem : inputVec)
        {
            result_1 += elem.length() - getLength(elem);
            result_2 += increaseLength(elem) - elem.length();
        }

		std::cout << "Day 08 - Part 1: " << result_1 << std::endl
				  << "Day 08 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY08