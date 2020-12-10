#ifndef ADVENTOFCODE2015_DAY09
#define ADVENTOFCODE2015_DAY09

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day09 {
private:
	std::string inputString;
public:
	Day09()
	{
		inputString = util::readFile("..\\inputs\\2015\\input_9.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		IntcodeVM vm1;
		std::vector<int64_t> input = { 1 };
		vm1.addInput(input);
		vm1.initializeCommands(commands);
		auto result1 = vm1.runCommands();
				
		IntcodeVM vm2;
		std::vector<int64_t> input2 = { 2 };
		vm2.addInput(input2);
		vm2.initializeCommands(commands);
		auto result2 = vm2.runCommands();

		std::cout << "Day 09, Part 1: " << result1[0] << std::endl
				  << "Day 09, Part 2: " << result2[0] << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY09