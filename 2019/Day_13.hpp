#ifndef ADVENTOFCODE2019_DAY13
#define ADVENTOFCODE2019_DAY13

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

#include <map>
#include <algorithm>

#define NOMINMAX
#include <Windows.h>

class Day13 {
private:
	void DrawMapClass(Map2DBase<int>& map, int score)
	{	
		std::map<int32_t, uint8_t> dict;
		dict[0] = ' ';
		dict[1] = static_cast<uint8_t>(0xFE);
		dict[2] = '#';
		dict[3] = '-';
		dict[4] = 'o';
		DrawMap(map.getMap(), dict);

		std::cout << "Score: " << score << std::endl;
		Sleep(30);
	}

	std::string input;
public:
	Day13()
	{
		input = util::readFile("..\\inputs\\2019\\input_13.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(input, ',');
		std::map<v2, int> tileMap;

		int result = 0;

		{
			IntcodeVM vm;
			vm.initializeCommands(commands);

			auto output = vm.runCommands();

			for (int index = 0; index < output.size(); index += 3)
			{
				v2 pos = v2(static_cast<int>(output[index]), static_cast<int>(output[index + 1]));
				tileMap[pos] = static_cast<int>(output[index + 2]);
			}


			for (auto elem : tileMap)
			{
				if (elem.second == 2)
					result++;
			}
		}
		int64_t minX, minY, maxX, maxY;
		minX = minY = std::numeric_limits<int64_t>::max();
		maxX = maxX = std::numeric_limits<int64_t>::min();

		for (auto elem : tileMap)
		{
			minX = std::min(minX, elem.first.x);
			maxX = std::max(maxX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxY = std::max(maxY, elem.first.y);
		}

		v2 size(maxX - minX + 1, maxY - minY + 1);
		Map2DBase<int> gameMap(0);

		for (auto elem : tileMap)
			gameMap.write(elem.first, elem.second);

		IntcodeVM vm;
		commands[0] = 2;
		vm.initializeCommands(commands);

		while (!vm.hasTerminated())
		{
			v2 currBall = gameMap.find(4);
			v2 currPad = gameMap.find(3);

			std::vector<int64_t> input = { sgn(currBall.x - currPad.x) };
			vm.addInput(input);

			auto output = vm.runCommands();

			for (int index = 0; index < output.size(); index += 3)
			{
				v2 pos = v2(static_cast<int>(output[index]), static_cast<int>(output[index + 1]));
				tileMap[pos] = static_cast<int>(output[index + 2]);

				if (gameMap.validIndex(pos))
					gameMap.write(pos, tileMap[pos]);
			}

			//DrawMapClass(gameMap, tileMap[v2(-1, 0)]);
		}

		std::cout << "Day 13 - Part 1: " << result << std::endl
				  << "Day 13 - Part 2: " << tileMap[v2(-1, 0)] << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY13