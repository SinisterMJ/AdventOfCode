#ifndef ADVENTOFCODE2019_DAY15
#define ADVENTOFCODE2019_DAY15

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

#define NOMINMAX
#include <Windows.h>

class Day15 {
private:
	const v2 north = v2(0, -1);
	const v2 south = v2(0, 1);
	const v2 west = v2(1, 0);
	const v2 east = v2(-1, 0);

	void DrawMapClass(std::map<v2, int>& map, v2 currentPos)
	{
		std::map<v2, int32_t> copy(map);

		int64_t minX = 0;
		int64_t minY = 0;
		int64_t maxX = 0;
		int64_t maxY = 0;
		for (auto elem : map)
		{
			minX = std::min(minX, elem.first.x);
			maxX = std::max(maxX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxY = std::max(maxY, elem.first.y);
		}
		for (int64_t y = minY; y <= maxY; ++y)
		{
			for (int64_t x = minX; x <= maxX; ++x)
			{
				if (copy.find(v2(x, y)) == copy.end())
					copy[v2(x, y)] = 4;
			}
		}
		
		copy[currentPos] = 3;

		std::map<int32_t, uint8_t> dict;
		dict[0] = 0xFE;
		dict[1] = '.';
		dict[2] = 'o';
		dict[3] = 'R';
		dict[4] = ' ';

		DrawMap(copy, dict);

		Sleep(15);
	}

	int64_t chooseDirection(std::map<v2, int>& oxygenMap, std::map<v2, int>& flood, v2& currentPos)
	{
		if (oxygenMap.find(currentPos + north) == oxygenMap.end())
		{
			return 1;
		}
		if (oxygenMap.find(currentPos + south) == oxygenMap.end())
		{
			return 2;
		}
		if (oxygenMap.find(currentPos + west) == oxygenMap.end())
		{
			return 3;
		}
		if (oxygenMap.find(currentPos + east) == oxygenMap.end())
		{
			return 4;
		}

		int val = flood[currentPos];

		if (flood.find(currentPos + north) != flood.end())
		{
			if (flood[currentPos + north] < val)
				return 1;
		}

		if (flood.find(currentPos + south) != flood.end())
		{
			if (flood[currentPos + south] < val)
				return 2;
		}

		if (flood.find(currentPos + west) != flood.end())
		{
			if (flood[currentPos + west] < val)
				return 3;
		}

		if (flood.find(currentPos + east) != flood.end())
		{
			if (flood[currentPos + east] < val)
				return 4;
		}

		return 1;
	}

	int64_t findShortestPath(std::vector<int64_t>& commands, std::map<v2, int>& oxygenMap)
	{
		IntcodeVM repairRobot;
		repairRobot.initializeCommands(commands);
		std::map<v2, int> floodFill;

		oxygenMap[v2(0, 0)] = 1;
		floodFill[v2(0, 0)] = 0;

		{
			bool mapcomplete = false;
			v2 currentPos;
			while (!mapcomplete)
			{
				int64_t input = chooseDirection(oxygenMap, floodFill, currentPos);
				std::vector<int64_t> inputV = { input };

				int step = floodFill[currentPos];

				repairRobot.addInput(inputV);
				auto output = repairRobot.runCommands();

				v2 direction;
				{
					if (input == 1)
						direction = north;
					if (input == 2)
						direction = south;
					if (input == 3)
						direction = west;
					if (input == 4)
						direction = east;
				}

				oxygenMap[currentPos + direction] = static_cast<int32_t>(output[0]);
				if (output[0] != 0)
				{
					currentPos += direction;
					if (floodFill.find(currentPos) == floodFill.end())
					{
						floodFill[currentPos] = step + 1;
					}
				}

				// DrawMapClass(oxygenMap, currentPos);

				if (currentPos == v2(0, 0))
				{
					if (oxygenMap.find(currentPos + north) != oxygenMap.end() &&
						oxygenMap.find(currentPos + south) != oxygenMap.end() &&
						oxygenMap.find(currentPos + west) != oxygenMap.end() &&
						oxygenMap.find(currentPos + east) != oxygenMap.end())
					{
						mapcomplete = true;;
					}
				}
			}
		}

		for (auto elem : oxygenMap)
		{
			if (elem.second == 2)
				return floodFill[elem.first];
		}

		return 0;
	}

	void fillFromOxygen(std::map<v2, int>& oxygenMap, std::map<v2, int>& bfsMap, v2 currentPos, int value)
	{
		if (bfsMap.find(currentPos + north) == bfsMap.end() && oxygenMap[currentPos + north] == 1)
			bfsMap[currentPos + north] = value + 1;

		if (bfsMap.find(currentPos + south) == bfsMap.end() && oxygenMap[currentPos + south] == 1)
			bfsMap[currentPos + south] = value + 1;

		if (bfsMap.find(currentPos + west) == bfsMap.end() && oxygenMap[currentPos + west] == 1)
			bfsMap[currentPos + west] = value + 1;

		if (bfsMap.find(currentPos + east) == bfsMap.end() && oxygenMap[currentPos + east] == 1)
			bfsMap[currentPos + east] = value + 1;
	}

	int64_t floodFromOxygen(std::map<v2, int>& oxygenMap)
	{
		std::map<v2, int> bfsMap;
		int totalCount = 0;
		v2 startPos;

		for (auto elem : oxygenMap)
		{
			if (elem.second == 2)
				startPos = elem.first;

			if (elem.second == 2 || elem.second == 1)
				totalCount++;
		}

		int val = 0;
		bfsMap[startPos] = val;

		while (bfsMap.size() < totalCount)
		{
			for (auto elem : bfsMap)
			{
				if (elem.second == val)
					fillFromOxygen(oxygenMap, bfsMap, elem.first, val);
			}
			val++;
		}


		return val;
	}

	std::string inputString;
public:
	Day15()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_15.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		std::map<v2, int> oxygenMap;

		int64_t result1 = findShortestPath(commands, oxygenMap);
		int64_t result2 = floodFromOxygen(oxygenMap);

		std::cout << "Day 15 - Part 1: " << result1 << std::endl
				  << "Day 15 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY15