#ifndef ADVENTOFCODE2019_DAY21
#define ADVENTOFCODE2019_DAY21

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>

class Day21 {
private:
	std::string inputString;

	int64_t surveySpringdroidRun(std::vector<int64_t>& commands)
	{
		IntcodeVM vm;
		vm.initializeCommands(commands);
		std::vector<std::string> instructions;
		
		instructions.push_back("NOT C J");
		instructions.push_back("NOT B T");
		instructions.push_back("OR T J");
		instructions.push_back("NOT A T");
		instructions.push_back("OR T J");
		instructions.push_back("AND D J");
		instructions.push_back("NOT H T");
		instructions.push_back("NOT T T");
		instructions.push_back("OR E T");
		instructions.push_back("AND T J");
		
		instructions.push_back("RUN\n");

		for (auto elem : instructions)
		{
			std::vector<int64_t> line;
			for (auto character : elem)
				line.push_back(character);
			
			line.push_back('\n');
			vm.addInput(line);
		}

		auto output = vm.runCommands();

		return output.back();
	}


	int64_t surveySpringdroid(std::vector<int64_t>& commands)
	{
		IntcodeVM vm;
		vm.initializeCommands(commands);
		std::vector<std::string> instructions;
	
		instructions.push_back("NOT C J");
		instructions.push_back("AND D J");
		instructions.push_back("NOT A T");
		instructions.push_back("OR T J");
		instructions.push_back("WALK");

		for (auto elem : instructions)
		{
			std::vector<int64_t> line;
			for (auto character : elem)
				line.push_back(character);

			line.push_back('\n');
			vm.addInput(line);
		}

		auto output = vm.runCommands();
		return output.back();
	}

public:
	Day21()
	{
		inputString = util::readFile("..\\inputs\\input_2019_21.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');

		int64_t result1 = surveySpringdroid(commands);
		int64_t result2 = surveySpringdroidRun(commands);

		std::cout << "Day 21 - Part 1: " << result1 << std::endl;
		std::cout << "Day 21 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY21