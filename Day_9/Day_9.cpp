#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdint.h>

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\inputs\\input_2019_9.txt");
	std::vector<int64_t> commands = util::splitInt64(inputString, ',');
	IntcodeVM vm1;
    std::vector<int64_t> input = { 1 };
    vm1.addInput(input);
	vm1.initializeCommands(commands);
	auto result1 = vm1.runCommands();

    std::cout << "Day 9, Part 1: " << result1[0] << std::endl;

    IntcodeVM vm2;
    std::vector<int64_t> input2 = { 2 };
    vm2.addInput(input2);
    vm2.initializeCommands(commands);
    auto result2 = vm2.runCommands();
	
    std::cout << "Day 9, Part 2: " << result2[0] << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}