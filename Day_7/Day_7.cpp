// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "../aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../IntcodeVM.h"

std::vector<int64_t> splitInt(const std::string &s, char delim) {
	std::vector<int64_t> elems;
	std::stringstream ss(s);
	std::string number;
	while (std::getline(ss, number, delim)) {
		elems.push_back(std::stoi(number));
	}
	return elems;
}

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\input_2019_7.txt");

	std::vector<int64_t> commands = splitInt(inputString, ',');
	std::vector<int64_t> inputs = { 0, 1, 2, 3, 4 };

	int64_t maxVal1 = std::numeric_limits<int64_t>::min();
	std::vector<int64_t> result = { 0 };
	
	do
	{
		result[0] = 0;
		result.resize(1);
		for (int index = 0; index < 5; index++)
		{
			IntcodeVM vm;
			vm.initializeCommands(commands);
			std::vector<int64_t> copy(2);
			copy[0] = inputs[index];
			copy[1] = result.at(result.size() - 1);
			vm.addInput(copy);
			result = vm.runCommands();
		}
		maxVal1 = std::max(maxVal1, result.at(result.size() - 1));
	} while (std::next_permutation(inputs.begin(), inputs.end()));
	
	std::cout << "Solution on AoC Day 7 Part 1: " << maxVal1 << std::endl;
	
	inputs = { 5, 6, 7, 8, 9 };
	
	std::vector<int64_t> input1[5];
	int64_t maxVal2 = std::numeric_limits<int64_t>::min();
	do
	{
		IntcodeVM vms[5];

		for (int index = 0; index < 5; index++)
		{
			std::vector<int64_t> input;
			input.push_back(inputs[index]);
			vms[index].addInput(input)->initializeCommands(commands);
		}

		result[0] = 0;
		result.resize(1);
		
		while (!vms[4].hasTerminated())
		{
			for (int index = 0; index < 5; index++)
			{
				vms[index].addInput(result);
				result = vms[index].runCommands();
			}
		}
		maxVal2 = std::max(maxVal2, result.at(result.size() - 1));
	} 
	while (std::next_permutation(inputs.begin(), inputs.end()));
		
	std::cout << "Solution on AoC Day 7 Part 2: " << maxVal2 << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}