#ifndef ADVENTOFCODE2016_DAY06
#define ADVENTOFCODE2016_DAY06

#include "../includes/aoc.h"
#include <regex>
#include <vector>
#include <memory>

class Day06 {
private:
	std::vector<std::string> inputVec;

    std::string part1()
    {
        std::string result = "";
        for (int index = 0; index < inputVec[0].size(); ++index)
        {
            std::map<char, int> letter_count;

            for (auto elem : inputVec)
                letter_count[elem[index]] += 1;

            int max = 0;

            for (auto [key, count] : letter_count)
                max = std::max(max, count);

            for (auto [key, count] : letter_count)
                if (count == max)
                    result += key;
        }

        return result;
    }

    std::string part2()
    {
        std::string result = "";
        for (int index = 0; index < inputVec[0].size(); ++index)
        {
            std::map<char, int> letter_count;

            for (auto elem : inputVec)
                letter_count[elem[index]] += 1;

            int min = inputVec.size();

            for (auto [key, count] : letter_count)
                min = std::min(min, count);

            for (auto [key, count] : letter_count)
                if (count == min)
                    result += key;
        }

        return result;
    }

public:
	Day06()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_6.txt");
	}

	int64_t run()
	{
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << std::endl
                  << "Day 06 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY06