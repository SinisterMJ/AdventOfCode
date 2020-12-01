#ifndef ADVENTOFCODE2019_DAY07
#define ADVENTOFCODE2019_DAY07

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day07 {
private:
	std::string inputString;
public:
	Day07()
	{
		inputString = util::readFile("..\\inputs\\input_2019_7.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		std::vector<int64_t> inputs = { 0, 1, 2, 3, 4 };

		int64_t maxVal1 = std::numeric_limits<int64_t>::min();
		std::vector<int64_t> result = { 0 };

		do
		{
			result = { 0 };

			for (int index = 0; index < 5; index++)
			{
				IntcodeVM vm;
				vm.initializeCommands(commands);
				std::vector<int64_t> copy(2);
				copy[0] = inputs[index];
				copy[1] = result.back();
				vm.addInput(copy);
				result = vm.runCommands();
			}
			maxVal1 = std::max(maxVal1, result.back());
		} while (std::next_permutation(inputs.begin(), inputs.end()));

		
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

			result = { 0 };

			while (!vms[4].hasTerminated())
			{
				for (int index = 0; index < 5; index++)
				{
					vms[index].addInput(result);
					result = vms[index].runCommands();
				}
			}
			maxVal2 = std::max(maxVal2, result.back());
		} while (std::next_permutation(inputs.begin(), inputs.end()));

		std::cout << "Day 07 - Part 1: " << maxVal1 << std::endl
				  << "Day 07 - Part 2: " << maxVal2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY07