#ifndef ADVENTOFCODE2016_DAY01
#define ADVENTOFCODE2016_DAY01

#include "../includes/Map2DBase.h"
#include "../includes/aoc.h"
#include <iostream>

class Day01 {
private:
    std::string input;
	std::vector<std::string> direction_list;

    int64_t part1()
    {
		auto neighbours = MapHelper::getNeighboursVec(false);
		int dir = 0;
		v2 pos(0, 0);

		for (auto& elem : direction_list)
		{
			if (elem[0] == 'R')
				dir = (dir + 1) % 4;
			if (elem[0] == 'L')
				dir = (dir + 3) % 4;

			int length = std::stoi(elem.substr(1));
			pos += neighbours[dir] * length;
		}

        return pos.manhattan();
    }

	int64_t part2()
	{
		auto neighbours = MapHelper::getNeighboursVec(false);
		int dir = 0;
		v2 pos(0, 0);
		std::set<v2> seen;
		seen.insert(pos);

		for (auto& elem : direction_list)
		{
			if (elem[0] == 'R')
				dir = (dir + 1) % 4;
			if (elem[0] == 'L')
				dir = (dir + 3) % 4;

			int length = std::stoi(elem.substr(1));

			for (int range = 0; range < length; ++range)
			{
				pos += neighbours[dir];

				if (seen.find(pos) != seen.end())
					return pos.manhattan();

				seen.insert(pos);
			}
		}

		return 0;
	}

public:
	Day01()
	{
		input = util::readFile("..\\inputs\\2016\\input_1.txt");
	}

	int64_t run()
	{	
		util::Timer myTime;
		myTime.start();

		direction_list = util::split(input, ',');

		for (auto& elem : direction_list)
		{
			if (elem[0] == ' ')
				elem = elem.substr(1);
		}
        		
        auto result_1 = part1();
        auto result_2 = part2();

		int64_t time = myTime.usPassed();

		std::cout << "Day 01 - Part 1: " << result_1 << std::endl
				  << "Day 01 - Part 2: " << result_2 << std::endl;

		return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY01