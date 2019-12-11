#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <map>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include "../includes/IntcodeVM.h"

struct Hull {
	v2 position;
	int color;
};

struct Visited {
	Hull setting;
	v2 dir;
	bool operator< (const Visited& a) const { 
		if (setting.color != a.setting.color)
			return setting.color < a.setting.color;
		if (setting.position == a.setting.position)
			return dir < a.dir; 
		return setting.position < a.setting.position;
	}
};

v2 turn(v2 in, int64_t dir)
{
	if (dir == 0)
	{
		if (in == v2(1, 0))
			return v2(0, 1);

		if (in == v2(0, 1))
			return v2(-1, 0);

		if (in == v2(-1, 0))
			return v2(0, -1);

		if (in == v2(0, -1))
			return v2(1, 0);
	}

	if (dir == 1)
	{
		if (in == v2(1, 0))
			return v2(0, -1);

		if (in == v2(0, -1))
			return v2(-1, 0);

		if (in == v2(-1, 0))
			return v2(0, 1);

		if (in == v2(0, 1))
			return v2(1, 0);
	}

	return v2(0, 0);
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFile("..\\inputs\\input_2019_11.txt");
	std::vector<int64_t> commands = util::splitInt64(input, ',');
	
	std::map<Visited, bool> alreadySeen;
	std::map<v2, int> currentColor;

	v2 pos(0, 0);

	Hull currentHull;
	currentHull.position.x = 0;
	currentHull.position.y = 0;
	currentHull.color = 0;
	v2 curDir = v2(0, 1);

	IntcodeVM vm;
	vm.initializeCommands(commands);

	do
	{
		std::vector<int64_t> input = { currentHull.color };
		vm.addInput(input);
		auto output = vm.runCommands();

		currentHull.color = output[0];
		currentColor[pos] = currentHull.color;

		curDir = turn(curDir, output[1]);
		pos += curDir;
		currentHull.color = 0;
		currentHull.position = pos;

		if (currentColor.find(pos) != currentColor.end())
		{
			currentHull.color = currentColor[pos];
		}

		Visited temp;
		temp.setting = currentHull;
		temp.dir = curDir;
	} while (!(vm.hasTerminated()));
	

	IntcodeVM vm2;
	vm2.initializeCommands(commands);
	std::map<v2, int> currentColor2;
	do
	{
		std::vector<int64_t> input = { currentHull.color };
		vm2.addInput(input);
		auto output = vm2.runCommands();

		currentHull.color = output[0];
		currentColor2[pos] = currentHull.color;

		curDir = turn(curDir, output[1]);
		pos += curDir;
		currentHull.color = 0;
		currentHull.position = pos;

		if (currentColor2.find(pos) != currentColor2.end())
		{
			currentHull.color = currentColor2[pos];
		}

		Visited temp;
		temp.setting = currentHull;
		temp.dir = curDir;
	} while (!vm2.hasTerminated());


	std::cout << "Part 1: " << currentColor.size() << std::endl;

	int minX = 0, maxX = 0;
	int minY = 0, maxY = 0;

	for (auto elem : currentColor2)
	{
		minX = std::min(minX, elem.first.x);
		maxX = std::max(minX, elem.first.x);
		minY = std::min(minY, elem.first.y);
		maxY = std::max(minY, elem.first.y);
	}

	std::string result = "";

	for (int y = maxY; y >= minY; --y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			v2 pos(x, y);
			if (currentColor2.find(pos) != currentColor2.end())
			{
				if (currentColor2[pos] == 1)
				{
					std::cout << "*";
					result += "#";
				}
				else
				{
					std::cout << " ";
					result += " ";
				}
			}
			else
			{
				std::cout << " ";
				result += " ";
			}
		}
		std::cout << std::endl;
		result += "\n";
	}

	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}