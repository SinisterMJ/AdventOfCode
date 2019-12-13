#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <regex>
#include <map>
#include <thread>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include "../includes/IntcodeVM.h"
#include <Windows.h>

void DrawMap(Map2DBase<int>& map)
{
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//position cursor at start of window
	destCoord.X = 0;
	destCoord.Y = 0;
	SetConsoleCursorPosition(hStdout, destCoord);

	std::string result = "";
	for (int y = 0; y < map.height(); ++y)
	{
		for (int x = 0; x < map.width(); ++x)
		{
			int val = map.read(x, y);

			if (val == 0)
				result += " ";
			if (val == 1)
				result += static_cast<unsigned char>(0xFE);
			if (val == 2)
				result += "#";
			if (val == 3)
				result += "_";
			if (val == 4)
				result += "o";
		}
		result += "\n";
	}
	std::cout << result << std::endl;
	Sleep(15);
}

int moveDecision(v2 v2_currBall, v2 v2_lastBall, v2 v2_currPad, v2& predictPosition, Map2DBase<int>& gameMap)
{
	return sgn(v2_currBall.x - v2_currPad.x);
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFile("..\\inputs\\input_2019_13.txt");
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

	auto firstElem = tileMap.begin();
	auto lastElem = (tileMap.end());
	lastElem--;

	v2 size(lastElem->first.x - firstElem->first.x + 1, lastElem->first.y - firstElem->first.y + 1);
	Map2DBase<int> gameMap(size, 0);

	v2 predictedPosition;

	for (auto elem : tileMap)
		gameMap.write(elem.first, elem.second);

	IntcodeVM vm;
	commands[0] = 2;
	vm.initializeCommands(commands);

	int nextDirection = 0;

	while (!vm.hasTerminated())
	{
		std::vector<int64_t> input = { nextDirection };
		vm.addInput(input);
		auto output = vm.runCommands();
		
		for (int index = 0; index < output.size(); index += 3)
		{
			v2 pos = v2(static_cast<int>(output[index]), static_cast<int>(output[index + 1]));
			tileMap[pos] = static_cast<int>(output[index + 2]);
		}

		for (auto elem : tileMap)
		{
			if (!gameMap.validIndex(elem.first))
				continue;

			gameMap.write(elem.first, elem.second);
		}

		//DrawMap(gameMap);
		
		v2 currBall = gameMap.find(4);
		v2 currPad = gameMap.find(3);
		nextDirection = sgn(currBall.x - currPad.x);
	}

	std::cout << std::endl << "Part 1: " << result << std::endl;
	std::cout << "Part 2: " << tileMap[v2(-1, 0)] << std::endl;
	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}