#ifndef ADVENTOFCODE2016_DAY05
#define ADVENTOFCODE2016_DAY05

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day05 {
private:
	std::vector<std::string> inputVec;

    bool CheckRule1(std::string input)
    {
        int64_t total = std::count(input.begin(), input.end(), 'a');
        total += std::count(input.begin(), input.end(), 'e');
        total += std::count(input.begin(), input.end(), 'i');
        total += std::count(input.begin(), input.end(), 'o');
        total += std::count(input.begin(), input.end(), 'u');

        return total > 2;
    }

    bool CheckRule2(std::string input)
    {
        for (int index = 1; index < input.size(); ++index)
        {
            if (input[index - 1] == input[index])
                return true;
        }

        return false;
    }

    bool CheckRule3(std::string input)
    {
        if (input.find("ab") != std::string::npos)
            return false;

        if (input.find("cd") != std::string::npos)
            return false;

        if (input.find("pq") != std::string::npos)
            return false;

        if (input.find("xy") != std::string::npos)
            return false;

        return true;
    }

    bool CheckRule4(std::string input)
    {
        for (int32_t index = 2; index < input.size(); ++index)
        {
            std::string test = input.substr(index - 2, 2);
            if (input.find(test, index) != std::string::npos)
                return true;
        }

        return false;
    }

    bool CheckRule5(std::string input)
    {
        for (int32_t index = 2; index < input.size(); ++index)
        {
            if (input[index - 2] == input[index])
                return true;
        }

        return false;
    }
public:
	Day05()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_5.txt");
	}

	int64_t run()
	{
        util::Timer myTime;
        myTime.start();

        auto result_1 = 0;
        auto result_2 = 0;

        for (auto elem : inputVec)
        {
            result_1 += CheckRule1(elem) & CheckRule2(elem) & CheckRule3(elem);
            result_2 += CheckRule4(elem) & CheckRule5(elem);
        }

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << std::endl
                  << "Day 05 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY05