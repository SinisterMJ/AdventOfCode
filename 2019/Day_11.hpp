#ifndef ADVENTOFCODE2019_DAY11
#define ADVENTOFCODE2019_DAY11

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

class Day11 {
private:
	struct Hull {
		v2 position;
		int color;
	};

	v2 turn(v2 in, int64_t dir)
	{
		dir = 2 * dir - 1;
		return v2(in.y * static_cast<int32_t>(dir), -in.x * static_cast<int32_t>(dir));
	}

	std::map<v2, int> runPaintJob(v2 startDir, int startColor, std::vector<int64_t>& commands)
	{
		std::map<v2, int> currentColor;

		Hull currentHull;
		currentHull.position = v2(0, 0);
		currentHull.color = startColor;
		v2 curDir = startDir;

		IntcodeVM vm;
		vm.initializeCommands(commands);

		do
		{
			std::vector<int64_t> input = { currentHull.color };
			vm.addInput(input);
			auto output = vm.runCommands();

			currentHull.color = static_cast<int32_t>(output[0]);
			currentColor[currentHull.position] = currentHull.color;

			curDir = turn(curDir, output[1]);
			currentHull.position += curDir;
			currentHull.color = 0;

			if (currentColor.find(currentHull.position) != currentColor.end())
			{
				currentHull.color = currentColor[currentHull.position];
			}
		} while (!(vm.hasTerminated()));

		return currentColor;
	}

	std::string inputString;
public:
	Day11()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_11.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');

		std::map<v2, int> currentColor1 = runPaintJob(v2(0, 1), 0, commands);
		std::map<v2, int> currentColor2 = runPaintJob(v2(0, 1), 1, commands);
				
		int minX = 0, maxX = 0;
		int minY = 0, maxY = 0;

		for (auto elem : currentColor2)
		{
			minX = std::min(minX, elem.first.x);
			maxX = std::max(maxX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxY = std::max(maxY, elem.first.y);
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
						result += static_cast<unsigned char>(0xFE);
					else
						result += " ";
				}
				else
					result += " ";
			}
			result += "\n";
		}
		
		std::cout << "Day 11 - Part 1: " << currentColor1.size() << std::endl
				  << "Day 11 - Part 2: " << std::endl 
				  << result << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY11