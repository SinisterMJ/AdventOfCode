#ifndef ADVENTOFCODE2019_DAY02
#define ADVENTOFCODE2019_DAY02

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day02 {
private:
	std::string inputString;
public:
	Day02()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');

		commands[1] = 12;
		commands[2] = 2;
		{
			IntcodeVM vm;
			vm.initializeCommands(commands);
			vm.runCommands();
			std::cout << "Day 02 - Part 1: " << vm.getFirstCommand() << std::endl;
		}

		{
			for (int i = 0; i < 100; ++i)
			{
				commands[1] = i;
				for (int j = 0; j < 100; ++j)
				{
					commands[2] = j;
					IntcodeVM vm;
					vm.initializeCommands(commands);
					vm.runCommands();

					if (vm.getFirstCommand() == 19690720)
					{
						std::cout << "Day 02 - Part 2: " << i * 100 + j << std::endl;
						goto solution_found;
					}
				}
			}
		}

	solution_found:
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY02