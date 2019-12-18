#ifndef ADVENTOFCODE2019_DAY18
#define ADVENTOFCODE2019_DAY18

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>

class Day18 {
private:
	const v2 north = v2(0, -1);
	const v2 south = v2(0, 1);
	const v2 west = v2(1, 0);
	const v2 east = v2(-1, 0);

	void buildMaze(std::vector<std::string>& input, Map2DBase<uint8_t>& maze, std::map<uint8_t, std::pair<v2, v2>>& doors)
	{
		for (int y = 0; y < input.size(); ++y)
		{
			for (int x = 0; x < input[y].length(); ++x)
			{
				maze.write(x, y, input[y][x]);
			}
		}

		for (uint8_t base = 'A', keys = 'a'; base <= 'Z'; ++base, ++keys)
		{
			v2 door = maze.find(base);
			v2 key = maze.find(keys);
			if (key != v2(-1, -1))
				doors[base] = std::make_pair(door, key);
		}
	}

	bool checkFloodable(Map2DBase<uint8_t>& maze, std::map<uint8_t, bool>& openDoors, v2 start)
	{
		if (maze.read(start) == '.')
			return true;

		if (maze.read(start) == '#')
			return false;

		uint8_t value = maze.read(start);

		if ('a' <= value && value <= 'z')
			return true;

		if ('A' <= value && value <= 'Z')
			return openDoors[value];

		return true;
	}

	bool floodTile(Map2DBase<uint8_t>& maze, std::map<v2, int>& flooded, std::map<uint8_t, bool>& openDoors, v2 currPos, int value)
	{
		if (flooded.find(currPos) == flooded.end() && checkFloodable(maze, openDoors, currPos))
		{
			flooded[currPos] = value;
			return true;
		}
		return false;
	}

	std::map<v2, int> stepsRequired(Map2DBase<uint8_t>& maze, std::map<uint8_t, bool>& openDoors, v2 start)
	{
		std::map<v2, int> flooded;
		flooded[start] = 0;
		v2 currPos = start;

		int currVal = 0;
				
		while (true)
		{
			bool writtenNewValue = false;

			for (auto elem : flooded)
			{
				if (elem.second != currVal)
					continue;

				if (floodTile(maze, flooded, openDoors, elem.first + north, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, openDoors, elem.first + east, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, openDoors, elem.first + west, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, openDoors, elem.first + south, currVal + 1))
					writtenNewValue = true;
			}

			if (!writtenNewValue)
				break;

			currVal++;
		}

		return flooded;
	}

	int64_t traverseMazeRecursively(Map2DBase<uint8_t>& maze, std::map<uint8_t, std::pair<v2, v2>>& doors, std::map<uint8_t, bool> openDoors, v2 currentPosition)
	{
		std::vector<std::pair<uint8_t, int32_t>> reachableKeys = { };
		bool allOpen = true;
		auto flooded = stepsRequired(maze, openDoors, currentPosition);
		for (auto elem : openDoors)
		{
			if (!elem.second)
			{
				if (flooded.find(doors[elem.first].second) != flooded.end())
				{
					reachableKeys.push_back(std::make_pair(elem.first, flooded[doors[elem.first].second]));
				}
			}
			allOpen &= elem.second;
		}
		
		if (allOpen)
			return 0;

		int64_t minSteps = std::numeric_limits<int64_t>::max();

		for (auto key : reachableKeys)
		{
			std::map<uint8_t, bool> copyOpenDoors(openDoors);
			copyOpenDoors[key.first] = true;
			minSteps = std::min(minSteps, key.second + traverseMazeRecursively(maze, doors, copyOpenDoors, doors[key.first].second));
		}

		return minSteps;
	}

	int64_t calcTotalSteps(Map2DBase<uint8_t>& maze, std::map<uint8_t, std::pair<v2, v2>>& doors)
	{
		std::map<uint8_t, bool> openDoors;
		for (auto elem : doors)
		{
			openDoors[elem.first] = false;
		}

		v2 currentPosition = maze.find('@');

		int64_t totalSteps = traverseMazeRecursively(maze, doors, openDoors, currentPosition);
		return totalSteps;
	}

	std::string inputString;
	std::vector<std::string> inputVector;
public:
	Day18()
	{
		inputString = util::readFile("..\\inputs\\input_2019_18.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2019_18.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		std::map<uint8_t, std::pair<v2, v2>> doors;
		Map2DBase<uint8_t> maze('.');
		
		buildMaze(inputVector, maze, doors);
		
		int64_t result1 = calcTotalSteps(maze, doors);
		
		std::cout << "Day 18 - Part 1: " << result1 << std::endl;
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY18