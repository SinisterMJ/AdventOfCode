#ifndef ADVENTOFCODE2015_DAY23
#define ADVENTOFCODE2015_DAY23

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

class Day23 {
private:
	std::string inputString;

	IntcodeVM vm[50];
	int64_t natValue[2];
	int64_t lastNatValue;

	int64_t result1;
	int64_t result2;

	std::vector<int64_t> inout;

	void runNetwork(std::vector<int64_t>& commands)
	{
		// Initialize VMs
		for (int index = 0; index < 50; ++index)
		{
			vm[index].initializeCommands(commands);
			std::vector<int64_t> input = { index, -1 };
			vm[index].addInput(input);			
		}

		while (true)
		{
			for (int index = 0; index < 50; ++index)
			{
				auto output = vm[index].runCommands();
				if (output.size() != 0)
				{
					inout.insert(inout.end(), output.begin(), output.end());
				}
			}

			// Send latest value to NAT
			if (inout.size() == 0)
			{
				if (lastNatValue == natValue[1])
				{
					result2 = natValue[1];
					break;
				}
				std::vector<int64_t> input = { natValue[0], natValue[1] };
				vm[0].addInput(input);

				lastNatValue = natValue[1];
			}

			for (int i = 0; i < inout.size(); )
			{
				std::vector<int64_t> input = { };

				int64_t index = inout[0];
				
				if (index == 255)
				{
					natValue[0] = inout[1];
					natValue[1] = inout[2];
					inout.erase(inout.begin(), inout.begin() + 3);

					if (result1 == -1)
						result1 = natValue[1];

					continue;
				}

				input.push_back(inout[1]);
				input.push_back(inout[2]);
				inout.erase(inout.begin(), inout.begin() + 3);
				vm[index].addInput(input);
			}
		}
	}

public:
	Day23() : result1(-1), result2(-1), lastNatValue(-1)
	{
		inputString = util::readFile("..\\inputs\\2015\\input_23.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		runNetwork(commands);
		
		std::cout << "Day 23 - Part 1: " << result1 << std::endl;
		std::cout << "Day 23 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY23