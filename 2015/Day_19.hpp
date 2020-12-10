#ifndef ADVENTOFCODE2015_DAY19
#define ADVENTOFCODE2015_DAY19

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>

class Day19 {
private:
	std::string inputString;
	
	int64_t calcResult1(std::vector<int64_t>& commands)
	{		
		int64_t result = 0;
		for (int y = 0; y < 50; ++y)
		{
			for (int x = 0; x < 50; ++x)
			{
				IntcodeVM vm;
				vm.initializeCommands(commands);

				std::vector<int64_t> input = { x, y };
				vm.addInput(input);
				auto output = vm.runCommands();
				result += output.back();
			}
		}
		return result;
	}

	int64_t getBeam(std::vector<int64_t>& commands, v2 pos)
	{
		IntcodeVM vm;
		vm.initializeCommands(commands);

		std::vector<int64_t> input = { pos.x, pos.y };
		vm.addInput(input);
		auto output = vm.runCommands();

		return output.back();
	}

	int64_t calcResult2(std::vector<int64_t>& commands)
	{
		int x = 99; int y = 0;

		while (true)
		{
			// Meet upper border of line.
			while (getBeam(commands, v2(x, y)) == 0)
				y++;
						
			if (getBeam(commands, v2(x - 99, y + 99)) == 1)
				return (x - 99) * 10000 + y;

			x++;
		}

		return 0;
	}

public:
	Day19()
	{
		inputString = util::readFile("..\\inputs\\2015\\input_19.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		
		int64_t result1 = calcResult1(commands);
		int64_t result2 = calcResult2(commands);

		std::cout << "Day 19 - Part 1: " << result1 << std::endl;
		std::cout << "Day 19 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY19