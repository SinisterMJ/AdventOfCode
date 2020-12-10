#ifndef ADVENTOFCODE2019_DAY05
#define ADVENTOFCODE2019_DAY05

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day05 {
private:
	std::string inputString;
public:
	Day05()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_5.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');

		{
			std::vector<int64_t> input = { 1 };
			IntcodeVM vm;
			vm.addInput(input);
			vm.initializeCommands(commands);

			auto result = vm.runCommands();
			std::cout << "Day 05 - Part 1: " << result.back() << std::endl;
		}

		{
			std::vector<int64_t> input = { 5 };
			IntcodeVM vm;
			vm.addInput(input);
			vm.initializeCommands(commands);

			auto result = vm.runCommands();
			std::cout << "Day 05 - Part 2: " << result.back() << std::endl;
		}
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY05