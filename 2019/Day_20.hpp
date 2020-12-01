#ifndef ADVENTOFCODE2019_DAY20
#define ADVENTOFCODE2019_DAY20

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>

class Day20 {
private:
	std::string inputString;
	std::vector<std::string> inputVector;
	std::map<int32_t, std::vector<v2>> portalMap;

	struct PositionDepth {
		v2 position;
		int32_t depth;

		bool operator < (const PositionDepth& b) const
		{
			if (position != b.position)
				return position < b.position;
			return depth < b.depth;
		}
	};

	void readBase(Map2DBase<int32_t>& maze)
	{
		for (int y = 0; y < inputVector.size(); ++y)
		{ 
			for (int x = 0; x < inputVector[y].length(); ++x)
			{
				uint8_t val = inputVector[y][x];
				v2 pos(x, y);

				if (val == '#' || val == '.')
					maze.write(pos, val);

				if (val == ' ')
					continue;

				if ('A' <= val && val <= 'Z')
				{
					int sx = x + 1;
					int sy = y + 1;
					uint8_t sval = 0;
					bool topDown = false;
					if (sy < inputVector.size() && x < inputVector[sy].length())
					{
						sval = inputVector[sy][x];
						if ('A' <= sval && sval <= 'Z')
							topDown = true;
						else
							sval = 0;
					}

					if (sx < inputVector[y].length() && !topDown)
					{
						sval = inputVector[y][sx];
						if ('A' <= sval && sval <= 'Z')
							topDown = false;
						else
							sval = 0;
						
					}

					if (sval > 0)
					{
						int32_t key = static_cast<int32_t>(val) * 256 + sval;
						if (topDown)
						{
							if ((y > 2 && y < inputVector.size() / 2) || (y > inputVector.size() - 3))
							{
								maze.write(x, y, key);
								portalMap[key].push_back(v2(x, y - 1));
							}
							else
							{
								maze.write(x, sy, key);
								portalMap[key].push_back(v2(x, sy + 1));
							}
						}
						else
						{
							if ((x > 2 && x < maze.width() / 2) || (x > maze.width() - 4))
							{
								maze.write(x, y, key);
								portalMap[key].push_back(v2(x - 1, y));
							}
							else
							{
								maze.write(sx, y, key);
								portalMap[key].push_back(v2(sx + 1, y));
							}
						}
					}
				}
			}
		}
	}

	std::vector<PositionDepth> getValidNeighboursRecursive(Map2DBase<int32_t>& maze, v2 current, int32_t currentLevel)
	{
		std::vector<PositionDepth> result;
		for (auto dir : maze.neighbours)
		{
			if (maze.read(current + dir) == '#')
				continue;

			int32_t val = maze.read(current + dir);
			PositionDepth entry;

			if (((val == 'A' * 256 + 'A') || (val == 'Z' * 256 + 'Z')) && currentLevel != 0)
				continue;
			
			v2 pos = current + dir;
			entry.depth = currentLevel;

			if (maze.read(pos) != '.')
			{
				bool innerPortal = true;

				if (pos.x == maze.minX() || pos.y == maze.minY() || pos.y == maze.maxY() || pos.x == maze.maxX())
					innerPortal = false;

				if (innerPortal)
					entry.depth += 1;

				if (!innerPortal)
				{
					if (currentLevel == 0)
						continue;

					entry.depth -= 1;
				}

				v2 portalOut = pos;
				auto portals = portalMap[val];

				if (portals.size() == 1)
					continue;

				pos = portals[0] == current ? portals[1] : portals[0];
			}

			entry.position = pos;
			result.push_back(entry);
		}

		return result;
	}

	std::vector<v2> getValidNeighbours(Map2DBase<int32_t>& maze, v2 current)
	{
		std::vector<v2> result;
		for (auto dir : maze.neighbours)
		{
			v2 pos = current + dir;
			auto val = maze.read(pos);

			if (val == '#')
				continue;
						
			if (val != '.')
			{
				auto portals = portalMap[val];
				if (portals.size() == 1)
					continue;

				pos = portals[0] == current ? portals[1] : portals[0];
			}

			result.push_back(pos);
		}

		return result;
	}

	int64_t calcStepsRecursiveDepth(Map2DBase<int32_t>& maze)
	{
		std::map<PositionDepth, int32_t> flooded;

		v2 start = maze.find('A' * 256 + 'A');

		for (auto dir : maze.neighbours)
		{
			if (maze.read(start + dir) == '.')
			{
				start = start + dir;
				break;
			}
		}

		v2 end = maze.find('Z' * 256 + 'Z');
		for (auto dir : maze.neighbours)
		{
			if (maze.read(end + dir) == '.')
			{
				end = end + dir;
				break;
			}
		}

		PositionDepth entry;
		entry.depth = 0;
		entry.position = start;

		PositionDepth entryEnd;
		entryEnd.depth = 0;
		entryEnd.position = end;
		
		int32_t value = 0;
		
		std::map<PositionDepth, int32_t> newlyAdded;
		flooded[entry] = value;
		newlyAdded[entry] = value;

		while (flooded.find(entryEnd) == flooded.end())
		{
			std::map<PositionDepth, int32_t> temp;
			for (auto elem : newlyAdded)
			{
				auto neighbours = getValidNeighboursRecursive(maze, elem.first.position, elem.first.depth);

				for (auto neighbour : neighbours)
				{
					if (flooded.find(neighbour) == flooded.end())
					{
						flooded[neighbour] = value + 1;
						temp[neighbour] = value + 1;
					}
				}
			}

			newlyAdded.swap(temp);

			++value;
		}

		std::cout << "Visited tiles: " << flooded.size() << std::endl;

		return flooded[entryEnd];
	}
	
	int64_t calcSteps(Map2DBase<int32_t>& maze)
	{
		std::map<v2, int32_t> flooded;
				
		v2 start = maze.find('A' * 256 + 'A');

		for (auto dir : maze.neighbours)
		{
			if (maze.read(start + dir) == '.')
			{
				start = start + dir;
				break;
			}
		}

		v2 end = maze.find('Z' * 256 + 'Z');
		for (auto dir : maze.neighbours)
		{
			if (maze.read(end + dir) == '.')
			{
				end = end + dir;
				break;
			}
		}

		int32_t value = 0;
		flooded[start] = value;
		
		while (flooded.find(end) == flooded.end())
		{
			for (auto elem : flooded)
			{
				if (elem.second == value)
				{
					auto neighbours = getValidNeighbours(maze, elem.first);

					for (auto neighbour : neighbours)
					{
						if (flooded.find(neighbour) == flooded.end())
							flooded[neighbour] = value + 1;
					}
				}
			}

			++value;
		}

		return flooded[end];
	}

public:
	Day20()
	{
		inputString = util::readFile("..\\inputs\\input_2019_20.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2019_20.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		Map2DBase<int32_t> plutoMaze('.');
		readBase(plutoMaze);

		int64_t result1 = calcSteps(plutoMaze);
		int64_t result2 = calcStepsRecursiveDepth(plutoMaze);

		std::cout << "Day 20 - Part 1: " << result1 << std::endl;
		std::cout << "Day 20 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY2
