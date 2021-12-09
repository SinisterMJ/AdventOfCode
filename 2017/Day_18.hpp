#ifndef ADVENTOFCODE2017_DAY18
#define ADVENTOFCODE2017_DAY18

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>

class Day18 {
private:
	std::vector<v2> neighbourTiles = MapHelper::getNeighboursVec(true);
	std::map<uint8_t, v2> keyMap;

	std::string inputString;
	std::vector<std::string> inputVector;

	void buildMaze(std::vector<std::string>& input, Map2DBase<uint8_t>& maze)
	{
		for (int y = 0; y < input.size(); ++y)
		{
			for (int x = 0; x < input[y].length(); ++x)
			{
				maze.write(x, y, input[y][x]);
			}
		}
	}

	int64_t part1(Map2DBase<uint8_t>& maze)
	{
		Map2DBase<uint8_t> start = maze;
		Map2DBase<uint8_t> temp = maze;

		for (int index = 0; index < 100; ++index)
		{
			for (int y = 0; y < maze.height(); ++y)
			{
				for (int x = 0; x < maze.width(); ++x)
				{
					v2 pos(x, y);
					bool turnedOn = (start.read(pos) == '#');
					int32_t countOn = 0;

					for (int neighbourIdx = 0; neighbourIdx < neighbourTiles.size(); ++neighbourIdx)
					{
						if (start.validIndex(pos + neighbourTiles[neighbourIdx]))
						{
							countOn += (start.read(pos + neighbourTiles[neighbourIdx]) == '#');
						}
					}

					if (turnedOn)
					{
						if (countOn == 2 || countOn == 3)
							temp.write(pos, '#');
						else
							temp.write(pos, '.');
					}
					else
					{
						temp.write(pos, countOn == 3 ? '#' : '.');						
					}
				}
			}

			std::swap(start, temp);
		}

		return start.countAll('#');
	}

	int64_t part2(Map2DBase<uint8_t>& maze)
	{
		Map2DBase<uint8_t> start = maze;
		Map2DBase<uint8_t> temp = maze;

		start.write(0, 0, '#');
		start.write(0, 99, '#');
		start.write(99, 0, '#');
		start.write(99, 99, '#');

		for (int index = 0; index < 100; ++index)
		{
			for (int y = 0; y < maze.height(); ++y)
			{
				for (int x = 0; x < maze.width(); ++x)
				{
					v2 pos(x, y);
					bool turnedOn = (start.read(pos) == '#');
					int32_t countOn = 0;

					for (int neighbourIdx = 0; neighbourIdx < neighbourTiles.size(); ++neighbourIdx)
					{
						if (start.validIndex(pos + neighbourTiles[neighbourIdx]))
						{
							countOn += (start.read(pos + neighbourTiles[neighbourIdx]) == '#');
						}
					}

					if (turnedOn)
					{
						if (countOn == 2 || countOn == 3)
							temp.write(pos, '#');
						else
							temp.write(pos, '.');
					}
					else
					{
						temp.write(pos, countOn == 3 ? '#' : '.');
					}
				}
			}

			std::swap(start, temp);

			start.write(0, 0, '#');
			start.write(0, 99, '#');
			start.write(99, 0, '#');
			start.write(99, 99, '#');
		}

		return start.countAll('#');
	}

public:
	Day18()
	{
		inputString = util::readFile("..\\inputs\\2017\\input_18.txt");
		inputVector = util::readFileLines("..\\inputs\\2017\\input_18.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
	
		Map2DBase<uint8_t> maze('.');
		buildMaze(inputVector, maze);

		int64_t result1 = part1(maze);
		int64_t result2 = part2(maze);

		std::cout << "Day 18 - Part 1: " << result1 << std::endl;
		std::cout << "Day 18 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY18