#ifndef ADVENTOFCODE2019_DAY18
#define ADVENTOFCODE2019_DAY18

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>
//#include <unordered_map>

class Day18 {
private:
	std::vector<v2> neighbourTiles = { v2(0, -1), v2(0, 1), v2(1, 0), v2(-1, 0) };
	std::vector<v2> diagonalTiles = { v2(-1, -1), v2(-1, 1), v2(1, 1), v2(1, -1) };
	std::map<uint8_t, v2> keyMap;

	struct State {
		v2 position;
		uint32_t acquiredKeys;
		int64_t steps;
		State(v2 _pos, uint32_t _keys, int64_t _steps) : position(_pos), acquiredKeys(_keys), steps(_steps) { }
	};

	struct StateTimeless {
		v2 position;
		uint32_t acquiredKeys;
		StateTimeless(v2 _pos, uint32_t _keys) : position(_pos), acquiredKeys(_keys) { }

		bool operator < (const StateTimeless& b) const 
		{
			if (position != b.position)
				return position < b.position;
			return acquiredKeys < b.acquiredKeys;
		}
	};

	struct StateQuad {
		std::vector<uint8_t> position;
		uint32_t acquiredKeys;
		bool operator < (const StateQuad& b) const
		{
			for (int index = 0; index < position.size(); ++index)
			{
				if (position[index] != b.position[index])
					return position[index] < b.position[index];
			}
			return acquiredKeys < b.acquiredKeys;
		}
	};

	struct StateQuadSteps {
		StateQuad state;
		int64_t steps;

		bool operator < (const StateQuadSteps& b) const
		{
			if (steps == b.steps)
				return state < b.state;

			return steps < b.steps;
		}

		bool operator == (const StateQuadSteps& a) const
		{
			return state.acquiredKeys == a.state.acquiredKeys;
		}
	};

	struct Keyset {
		uint32_t mask;
		int32_t count;
		Keyset() : mask(0), count(0) { }

		bool isSet(int i)
		{
			if (i < 0)
				return false;

			return (mask & (1 << i));
		}

		void set(int i) {
			if (isSet(i))
				return;
			if (i < 0)
				return;
			mask |= (1 << i);
			count++;
		}

		void unset(int i) {
			if (isSet(i))
			{ 
				count--;
				mask &= ~(1 << i);
			}
		}
	};

	std::string inputString;
	std::vector<std::string> inputVector;

	void buildMaze(std::vector<std::string>& input, Map2DBase<uint8_t>& maze, Keyset& keyset)
	{
		for (int y = 0; y < input.size(); ++y)
		{
			for (int x = 0; x < input[y].length(); ++x)
			{
				maze.write(x, y, input[y][x]);

				if ('a' <= input[y][x] && input[y][x] <= 'z')
				{
					uint8_t key = input[y][x];
					keyset.set(key - 'a');
					keyMap[input[y][x]] = v2(x, y);
				}
			}
		}
	}

	int64_t calcSteps(Map2DBase<uint8_t>& map, Keyset keys)
	{
		std::deque<State> checkItems;
		std::set<StateTimeless> seen = { };

		checkItems.push_back(State(map.find('@'), 0, 0));
		seen.insert(StateTimeless(map.find('@'), 0));

		while (checkItems.size() > 0)
		{
			State check = checkItems.front();
			checkItems.pop_front();

			if (check.acquiredKeys == keys.mask)
			{
				return check.steps;
			}

			for (auto dir : neighbourTiles)
			{
				v2 newPos = check.position + dir;
				uint8_t val = map.read(newPos);

				if (val == '#')
					continue;

				if ('A' <= val && val <= 'Z')
				{
					if (!(check.acquiredKeys & (1 << (val - 'A'))))
						continue;
				}

				State nextState(newPos, check.acquiredKeys, check.steps + 1);

				if ('a' <= val && val <= 'z')
				{
					nextState.acquiredKeys |= 1 << (val - 'a');
				}

				StateTimeless situation(nextState.position, nextState.acquiredKeys);

				if (seen.find(situation) != seen.end())
					continue;

				seen.insert(situation);
				checkItems.push_back(nextState);
			}
		}

		return -1;
	}

	bool floodTile(Map2DBase<uint8_t>& maze, std::map<v2, int>& flooded, v2 currPos, int value)
	{
		if (flooded.find(currPos) == flooded.end() && maze.read(currPos) != '#')
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

				for (auto dir : neighbourTiles)
				{
					if (floodTile(maze, flooded, elem.first + dir, currVal + 1))
						writtenNewValue = true;
				}
			}

			if (!writtenNewValue)
				break;

			currVal++;
		}

		return flooded;
	}

	uint32_t getDoorMask(Map2DBase<uint8_t>& maze, std::map<v2, int>& stepMap, v2 start)
	{
		uint32_t mask = 0;

		int pathLength = stepMap[start];
		v2 curr = start;

		while (pathLength > 0)
		{
			v2 direction;
			for (auto dir : neighbourTiles)
			{
				if (stepMap.find(curr + dir) != stepMap.end() && stepMap[curr + dir] < stepMap[curr])
					direction = dir;
			}

			pathLength--;
			curr += direction;

			if ('A' <= maze.read(curr) && maze.read(curr) <= 'Z')
				mask |= (1 << (maze.read(curr) - 'A'));
		}

		return mask;
	}

	std::map<std::pair<uint8_t, uint8_t>, std::pair<int32_t, uint32_t>> findMaskRobot(Map2DBase<uint8_t>& map, v2 startPosition)
	{
		std::map<std::pair<uint8_t, uint8_t>, std::pair<int32_t, uint32_t>> result;

		auto robotMap = stepsRequired(map, startPosition);

		for (auto key : keyMap)
		{
			if (robotMap.find(key.second) != robotMap.end())
			{
				int32_t value = robotMap[key.second];
				uint32_t mask = getDoorMask(map, robotMap, key.second);

				result[std::make_pair('@', key.first)] = std::make_pair(value, mask);

				auto mapFromKey = stepsRequired(map, key.second);
				for (auto targetKey : keyMap)
				{
					if (mapFromKey.find(targetKey.second) != mapFromKey.end())
					{
						int32_t value = mapFromKey[targetKey.second];
						uint32_t mask = getDoorMask(map, mapFromKey, targetKey.second);
						result[std::make_pair(key.first, targetKey.first)] = std::make_pair(value, mask);
					}
				}
			}
		}
		
		return result;
	}

	std::vector<std::pair<uint8_t, int32_t>> getReachableNodes(std::map<std::pair<uint8_t, uint8_t>, std::pair<int32_t, uint32_t>>& robotMap, uint32_t currentKeys, uint8_t currentPosition)
	{
		std::vector<std::pair<uint8_t, int32_t>> result;

		for (auto maps : robotMap)
		{
			if (currentKeys & (1 << (maps.first.second - 'a')))
				continue;
			
			if (maps.first.first == currentPosition)
			{
				if ((maps.second.second & currentKeys) == maps.second.second)
				{
					result.push_back(std::make_pair(maps.first.second, maps.second.first));
				}
			}
		}
		
		return result;
	}

	int64_t calcStepsPart2(Map2DBase<uint8_t>& map, Keyset keys)
	{
		auto startPosRobots = map.findAll('@');
		std::vector<uint8_t> positionsRobots = { '@', '@', '@', '@' };

		std::vector<std::map<std::pair<uint8_t, uint8_t>, std::pair<int32_t, uint32_t>>> reachablePerRobotMap;
		
		reachablePerRobotMap.resize(startPosRobots.size());
		
		for (uint32_t index = 0; index < startPosRobots.size(); ++index)
		{
			reachablePerRobotMap[index] = findMaskRobot(map, startPosRobots[index]);
		}

		std::set<StateQuad> seen;
		std::vector<StateQuadSteps> statuses;

		StateQuad initial;
		initial.position = positionsRobots;
		initial.acquiredKeys = 0;

		StateQuadSteps initialTime;
		initialTime.state = initial;
		initialTime.steps = 0;

		statuses.push_back(initialTime);

		while (statuses.size() > 0)
		{
			auto stateTime = statuses.front();
			statuses.erase(statuses.begin(), statuses.begin() + 1);
			
			if (stateTime.state.acquiredKeys == keys.mask)
			{
				return stateTime.steps;
			}

			if (seen.find(stateTime.state) != seen.end())
				continue;

			seen.insert(stateTime.state);

			std::vector<std::vector<std::pair<uint8_t, int32_t>>> reachPerMap;
			std::vector<std::vector<std::pair<uint8_t, int32_t>>> possibleSteps;

			for (int index = 0; index < 4; ++index)
			{
				reachPerMap.push_back(getReachableNodes(reachablePerRobotMap[index], stateTime.state.acquiredKeys, stateTime.state.position[index]));
				if (reachPerMap[index].size() == 0)
				{
					reachPerMap[index].push_back(std::make_pair(stateTime.state.position[index], 0));
				}			
			}

			for (int i = 0; i < reachPerMap[0].size(); ++i)
			{
				for (int j = 0; j < reachPerMap[1].size(); ++j)
				{
					for (int k = 0; k < reachPerMap[2].size(); ++k)
					{
						for (int l = 0; l < reachPerMap[3].size(); ++l)
						{
							std::vector<std::pair<uint8_t, int32_t>> local;
							local.push_back(reachPerMap[0][i]);
							local.push_back(reachPerMap[1][j]);
							local.push_back(reachPerMap[2][k]);
							local.push_back(reachPerMap[3][l]);
							possibleSteps.push_back(local);
						}
					}
				}
			}

			for (auto possibilites : possibleSteps)
			{
				StateQuadSteps entry;
				entry.steps = stateTime.steps + possibilites[0].second + possibilites[1].second + possibilites[2].second + possibilites[3].second;
				entry.state.acquiredKeys = stateTime.state.acquiredKeys;
				entry.state.position = stateTime.state.position;
								
				entry.state.position[0] = possibilites[0].first;
				entry.state.position[1] = possibilites[1].first;
				entry.state.position[2] = possibilites[2].first;
				entry.state.position[3] = possibilites[3].first;
				entry.state.acquiredKeys |= (1 << (possibilites[0].first - 'a'));
				entry.state.acquiredKeys |= (1 << (possibilites[1].first - 'a'));
				entry.state.acquiredKeys |= (1 << (possibilites[2].first - 'a'));
				entry.state.acquiredKeys |= (1 << (possibilites[3].first - 'a'));

				statuses.push_back(entry);
			}

			std::sort(statuses.begin(), statuses.end());
			statuses.erase(std::unique(statuses.begin(), statuses.end()), statuses.end());
		}

		return 0;
	}

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
		Keyset keys;
		Map2DBase<uint8_t> maze('.');
		Map2DBase<uint8_t> mazePart2('.');

		buildMaze(inputVector, maze, keys);
		buildMaze(inputVector, mazePart2, keys);

		v2 changePart2 = mazePart2.find('@');
		mazePart2.write(changePart2, '#');
		for (auto dir : neighbourTiles)
			mazePart2.write(changePart2 + dir, '#');

		for (auto dir : diagonalTiles)
			mazePart2.write(changePart2 + dir, '@');

		int64_t result2 = calcStepsPart2(mazePart2, keys);
		int64_t result1 = calcSteps(maze, keys);

		std::cout << "Day 18 - Part 1: " << result1 << std::endl;
		std::cout << "Day 18 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY18