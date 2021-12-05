#ifndef ADVENTOFCODE2017_DAY03
#define ADVENTOFCODE2017_DAY03

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

#include <iostream>
#include <vector>
#include <set>

class Day03 {
private:
	int32_t number{ 277678 };


	int32_t part1()
	{
		std::map<v2, int32_t> memory;
		v2 dir(0, -1);
		v2 position(0, 0);
		memory[position] = 1;

		for (int i = 2; i <= number; ++i)
		{
			auto new_dir = Map2DBase<int32_t>::turnLeft(dir);
			if (memory.find(position + new_dir) == memory.end())
			{
				dir = new_dir;
			}

			position += dir;
			memory[position] = i;
		}

		return std::abs(position.x) + std::abs(position.y);
	}

	int32_t part2()
	{
		std::map<v2, int32_t> memory;
		v2 dir(0, -1);
		v2 position(0, 0);
		memory[position] = 1;
		auto allNeighbours = Map2DBase<int32_t>::getNeighboursVec(true);
		
		for (;;)
		{
			auto new_dir = Map2DBase<int32_t>::turnLeft(dir);
			if (memory.find(position + new_dir) == memory.end())
			{
				dir = new_dir;
			}

			position += dir;
			
			int val = 0;

			for (auto neighbour : allNeighbours)
			{
				if (memory.find(position + neighbour) != memory.end())
				{
					val += memory[position + neighbour];
				}
			}

			memory[position] = val;

			if (val >= number)
				return val;
		}

		return 0;
	}

public:
	Day03()
	{
		
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

#endif  // ADVENTOFCODE2017_DAY03