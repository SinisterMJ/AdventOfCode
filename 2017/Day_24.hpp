#ifndef ADVENTOFCODE2017_DAY24
#define ADVENTOFCODE2017_DAY24

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <regex>

class Day24 {
private:
	std::string inputString;
	std::vector<std::string> inputVector; 
	
	std::vector<v2> neighbours = { v2(0, -1), v2(0, 1), v2(1, 0), v2(-1, 0) };
	
	std::vector<v3> getNeighbours(v3 input)
	{
		std::vector<v3> recursiveNeighbours;
		
		v2 pos(input.x, input.y);

		for (auto dir : neighbours)
		{
			v2 curr = pos + dir;

			if (curr.x >= 0 && curr.x < 5 && 
				curr.y >= 0 && curr.y < 5 && 
				(curr.x != 2 || curr.y != 2))
			{
				recursiveNeighbours.push_back(v3(curr.x, curr.y, input.z));
			}

			if (curr.x == -1)
			{
				recursiveNeighbours.push_back(v3(1, 2, input.z - 1));
			}
			if (curr.y == -1)
			{
				recursiveNeighbours.push_back(v3(2, 1, input.z - 1));
			}
			if (curr.x == 5)
			{
				recursiveNeighbours.push_back(v3(3, 2, input.z - 1));
			}
			if (curr.y == 5)
			{
				recursiveNeighbours.push_back(v3(2, 3, input.z - 1));
			}

			if (curr.x == 2 && curr.y == 2)
			{
				if (pos.y != 2)
				{
					int32_t y = pos.y * 2 - 2;
					for (int x = 0; x < 5; ++x)
						recursiveNeighbours.push_back(v3(x, y, input.z + 1));
				}

				if (pos.x != 2)
				{
					int32_t x = pos.x * 2 - 2;
					for (int y = 0; y < 5; ++y)
						recursiveNeighbours.push_back(v3(x, y, input.z + 1));
				}
			}
		}

		return recursiveNeighbours;
	}

	int64_t calcSecond()
	{
		int64_t result = 0;

		std::map<v3, uint8_t> bugMap;

		for (int y = 0; y < inputVector.size(); ++y)
		{
			for (int x = 0; x < inputVector[y].length(); ++x)
			{
				bugMap[v3(x, y, 0)] = inputVector[y][x];
			}
		}

		int32_t time = 0;
		int32_t minLevel = -1;
		int32_t maxLevel = +1;
		while (time < 200)
		{
			std::map<v3, uint8_t> bugMapTemp;
			for (int z = minLevel; z <= maxLevel; ++z)
			{
				for (int y = 0; y < 5; ++y)
				{
					for (int x = 0; x < 5; ++x)
					{
						if (x == 2 && y == 2)
							continue;

						v3 pos(x, y, z);
						int32_t neighbourCount = 0;

						auto neighbours = getNeighbours(pos);

						for (auto check : neighbours)
						{
							if (bugMap.find(check) != bugMap.end())
							{
								neighbourCount += (bugMap[check] == '#');
							}
						}

						if ((neighbourCount == 1) || (neighbourCount == 2 && (bugMap[pos] != '#')))
						{
							bugMapTemp[pos] = '#';	
							minLevel = std::min(minLevel, pos.z - 1);
							maxLevel = std::max(maxLevel, pos.z + 1);
						}
						else
						{
							bugMapTemp[pos] = '.';
						}
					}
				}
			}

			bugMap.swap(bugMapTemp);
			time++;
		}
		
		for (auto elem : bugMap)
		{
			if (elem.second == '#')
				result++;
		}

		return result;
	}

	int64_t calcFirst()
	{
		int64_t result = 0;

		std::map<v2, uint8_t> bugMap;

		for (int y = 0; y < inputVector.size(); ++y)
		{
			for (int x = 0; x < inputVector[y].length(); ++x)
			{
				if (x == 2 && y == 2)
					continue;

				bugMap[v2(x, y)] = inputVector[y][x];
			}
		}

		std::set<int32_t> states;
		int32_t currentState = 0;

		while (true)
		{
			std::map<v2, uint8_t> bugMapTemp;

			currentState = 0;
			for (int y = 0; y < 5; ++y)
			{
				for (int x = 0; x < 5; ++x)
				{
					uint8_t offset = y * 5 + x;
					if (bugMap[v2(x, y)] == '#')
					{
						currentState |= 1 << offset;
					}
				}
			}

			if (states.find(currentState) != states.end())
			{
				break;
			}
	
			states.insert(currentState);

			for (int y = 0; y < 5; ++y)
			{
				for (int x = 0; x < 5; ++x)
				{
					v2 pos(x, y);
					int32_t neighbourCount = 0;

					for (auto dir : neighbours)
					{
						v2 check = pos + dir;
						if (bugMap.find(check) != bugMap.end())
						{
							neighbourCount += (bugMap[check] == '#');
						}

						if (neighbourCount == 1)
							bugMapTemp[pos] = '#';
						else if (neighbourCount == 2 && bugMap[pos] == '.')
							bugMapTemp[pos] = '#';
						else
							bugMapTemp[pos] = '.';
					}
				}
			}
			
			bugMap.swap(bugMapTemp);
		}

		result = currentState;


		return result;
	}

	
public:
	Day24()
	{
		inputString = util::readFile("..\\inputs\\2017\\input_24.txt");
		inputVector = util::readFileLines("..\\inputs\\2017\\input_24.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		int64_t result1 = calcFirst();
		int64_t result2 = calcSecond();

		std::cout << "Day 24 - Part 1: " << result1 << std::endl;
		std::cout << "Day 24 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY24