// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\inputs\\input_2019_5.txt");
	std::vector<int64_t> commands = util::splitInt64(inputString, ',');

    {
        std::vector<int64_t> input = { 1 };
        IntcodeVM vm;
        vm.addInput(input);
        vm.initializeCommands(commands);

        auto result = vm.runCommands();
        std::cout << "Solution on AoC Day 5 Part 1: " << result.back() << std::endl;
    }
	
    {
        std::vector<int64_t> input = { 5 };
        IntcodeVM vm;
        vm.addInput(input);
        vm.initializeCommands(commands);

        auto result = vm.runCommands();
        std::cout << "Solution on AoC Day 5 Part 2: " << result.back() << std::endl;
    }

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}