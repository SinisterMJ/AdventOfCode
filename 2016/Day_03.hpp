#ifndef ADVENTOFCODE2016_DAY03
#define ADVENTOFCODE2016_DAY03

#include "../includes/aoc.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>

class Day03 {
private:
	std::vector<std::string> inputVec;
	

	int part1()
	{
		int result = 0;

		for (auto elem : inputVec)
		{
			std::vector<int> sides = util::splitInt(elem, ' ');
			
			std::sort(sides.begin(), sides.end());
			result += ((sides[0] + sides[1]) > sides[2]);
		}

		return result;
	}

	int part2()
	{
		std::vector<std::vector<int>> sides;
		int result = 0;

		for (auto elem : inputVec)
			sides.emplace_back(util::splitInt(elem, ' '));

		for (int i = 0; i < sides.size(); i += 3)
		{
			for (int j = 0; j < 3; ++j)
			{
				std::vector<int> triangle;
				triangle.emplace_back(sides[i + 0][j]);
				triangle.emplace_back(sides[i + 1][j]);
				triangle.emplace_back(sides[i + 2][j]);

				std::sort(triangle.begin(), triangle.end());
				result += ((triangle[0] + triangle[1]) > triangle[2]);

			}
		}

		return result;
	}

public:
	Day03()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        auto result_1 = part1();
        auto result_2 = part2();
        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << std::endl
                  << "Day 03 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY03