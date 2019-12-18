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

	bool checkFloodable(Map2DBase<uint8_t>& maze, v2 start)
	{
		if (maze.read(start) == '#')
			return false;
		
		return true;
	}

	bool floodTile(Map2DBase<uint8_t>& maze, std::map<v2, int>& flooded, v2 currPos, int value)
	{
		if (flooded.find(currPos) == flooded.end() && checkFloodable(maze, currPos))
		{
			flooded[currPos] = value;
			return true;
		}

		return false;
	}

	std::map<v2, int> stepsRequired(Map2DBase<uint8_t>& maze, v2 start)
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

				if (floodTile(maze, flooded, elem.first + north, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, elem.first + east, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, elem.first + west, currVal + 1))
					writtenNewValue = true;
				if (floodTile(maze, flooded, elem.first + south, currVal + 1))
					writtenNewValue = true;
			}

			if (!writtenNewValue)
				break;

			currVal++;
		}

		return flooded;
	}

	std::map<uint8_t, std::pair<int, std::vector<uint8_t>>> buildTraverseItem(Map2DBase<uint8_t>& maze, std::map<v2, int>& stepMap)
	{
		std::map<uint8_t, std::pair<int, std::vector<uint8_t>>> traverseMap;
		for (uint8_t base = 'a'; base <= 'z'; ++base)
		{
			v2 target = maze.find(base);
			v2 lookUp = target;
			int steps = stepMap[target];

			int pathLength = steps;

			std::vector<uint8_t> doorsPassed = { };

			while (pathLength > 0)
			{
				v2 direction;
				if (stepMap.find(lookUp + north) != stepMap.end() && stepMap[lookUp + north] < pathLength)
					direction = north;

				if (stepMap.find(lookUp + east) != stepMap.end() && stepMap[lookUp + east] < pathLength)
					direction = east;

				if (stepMap.find(lookUp + south) != stepMap.end() && stepMap[lookUp + south] < pathLength)
					direction = south;

				if (stepMap.find(lookUp + west) != stepMap.end() && stepMap[lookUp + west] < pathLength)
					direction = west;

				pathLength--;
				lookUp += direction;

				if ('A' <= maze.read(lookUp) && maze.read(lookUp) <= 'Z')
					doorsPassed.push_back(maze.read(lookUp));
			}

			traverseMap[base] = std::make_pair(steps, doorsPassed);
		}

		return traverseMap;
	}
	   
	void buildTraverse(Map2DBase<uint8_t>& maze, std::map<uint8_t, std::pair<v2, v2>>& doors, std::map<uint8_t, std::map<uint8_t, std::pair<int, std::vector<uint8_t>>>>& traverseMap)
	{
		for (auto elem : doors)
		{
			uint8_t keyFrom = elem.first - 'A' + 'a';
			auto stepMap = stepsRequired(maze, elem.second.second);
			traverseMap[keyFrom] = buildTraverseItem(maze, stepMap);
		}

		uint8_t keyFrom = '0';
		auto stepMap = stepsRequired(maze, maze.find('@'));
		traverseMap[keyFrom] = buildTraverseItem(maze, stepMap);
	}

	int64_t traverseMapRecursively(std::map<uint8_t, std::map<uint8_t, std::pair<int, std::vector<uint8_t>>>>& traverseMap, std::vector<uint8_t> acquiredKeys, uint8_t currPos, int depth)
	{
		std::vector<uint8_t> reachableKeys = { };
		for (auto elem : traverseMap[currPos])
		{
			if (std::find(acquiredKeys.begin(), acquiredKeys.end(), elem.first + 'A' - 'a') != acquiredKeys.end())
			{
				continue;
			}
			bool pathFree = true;
			for (auto door : elem.second.second)
			{
				if (std::find(acquiredKeys.begin(), acquiredKeys.end(), door) == acquiredKeys.end())
					pathFree = false;
			}
			if (pathFree)
			{
				reachableKeys.push_back(elem.first);
			}
		}

		if (reachableKeys.size() == 0)
			return 0;

		int64_t minSteps = std::numeric_limits<int64_t>::max();

		int64_t count = reachableKeys.size();
		for (auto key : reachableKeys)
		{
			std::vector<uint8_t> copyKeys(acquiredKeys);
			copyKeys.push_back(key + 'A' - 'a');
			int sanity = traverseMap[currPos][key].first;
			minSteps = std::min(minSteps, traverseMap[currPos][key].first + traverseMapRecursively(traverseMap, copyKeys, key, depth + 1));
			if (depth < 5)
			{
				std::cout << "Depth: " << depth << " Items remaining: " << --count << std::endl;
			}
		}

		return minSteps;
	}

	int64_t calcStepsFromTraverseMap(std::map<uint8_t, std::map<uint8_t, std::pair<int, std::vector<uint8_t>>>>& traverseMap)
	{
		uint8_t start = '0';
		std::vector<uint8_t> acquiredKeys = { };
		int64_t totalSteps = traverseMapRecursively(traverseMap, acquiredKeys, '0', 1);
		return 0;
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
		std::map<uint8_t, std::map<uint8_t, std::pair<int, std::vector<uint8_t>>>> traverseMap;
		Map2DBase<uint8_t> maze('.');
		
		buildMaze(inputVector, maze, doors);
		buildTraverse(maze, doors, traverseMap);
		
		int64_t result1 = calcStepsFromTraverseMap(traverseMap);
		
		std::cout << "Day 18 - Part 1: " << result1 << std::endl;
		
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY18