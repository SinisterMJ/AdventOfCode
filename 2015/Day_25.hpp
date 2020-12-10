#ifndef ADVENTOFCODE2015_DAY25
#define ADVENTOFCODE2015_DAY25

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>

class Day25 {
private:
	std::string inputString;
	std::vector<std::string> inventory;

	std::vector<int64_t> stringToInput(std::string input)
	{
		std::vector<int64_t> result = { };
		for (auto elem : input)
		{
			result.push_back(elem);
		}

		return result;
	}

	std::string outputToString(std::vector<int64_t> input)
	{
		std::string temp = "";
		for (auto elem : input)
		{
			temp += static_cast<uint8_t>(elem);
			
		}
		return temp;
	}

	std::string runDiscovery(std::vector<int64_t>& commands)
	{
		std::string result = "";

		IntcodeVM vm;
		vm.initializeCommands(commands);

		vm.addInput(stringToInput("east\n"));
		vm.addInput(stringToInput("take weather machine\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("take bowl of rice\n"));
		vm.addInput(stringToInput("east\n"));
		vm.addInput(stringToInput("north\n"));
		vm.addInput(stringToInput("take polygon\n"));
		vm.addInput(stringToInput("east\n"));
		vm.addInput(stringToInput("take hypercube\n"));
		vm.addInput(stringToInput("south\n"));
		vm.addInput(stringToInput("take dark matter\n"));
		vm.addInput(stringToInput("north\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("north\n"));
		vm.addInput(stringToInput("take candy cane\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("north\n"));
		vm.addInput(stringToInput("take manifold\n"));
		vm.addInput(stringToInput("south\n"));
		vm.addInput(stringToInput("west\n"));
		vm.addInput(stringToInput("north\n"));
		vm.addInput(stringToInput("take dehydrated water\n"));
		vm.addInput(stringToInput("west\n"));

		
		v2 start;
		int32_t pathValue = 0;
		uint8_t currentSet = 0;
		while (!vm.hasTerminated())
		{
			auto output = outputToString(vm.runCommands());
			result = output;

			for (int i = 0; i < 8; ++i)
			{
				vm.addInput(stringToInput("drop " + inventory[i] + "\n"));
			}

			for (int i = 0; i < 8; ++i)
			{
				if ((currentSet >> i) & 0x1)
					vm.addInput(stringToInput("take " + inventory[i] + "\n"));
			}

			currentSet++;
			vm.addInput(stringToInput("south\n"));
		}

		return result;
	}

public:
	Day25()
	{
		inputString = util::readFile("..\\inputs\\2015\\input_25.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		inventory.push_back("manifold");
		inventory.push_back("dehydrated water");
		inventory.push_back("polygon");
		inventory.push_back("weather machine");
		inventory.push_back("bowl of rice");
		inventory.push_back("hypercube");
		inventory.push_back("candy cane");
		inventory.push_back("dark matter");

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');

		std::string result1 = runDiscovery(commands);

		std::cout << "Day 25 - Part 1: " << result1 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY25