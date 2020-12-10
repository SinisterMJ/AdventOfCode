#ifndef ADVENTOFCODE2019_DAY01
#define ADVENTOFCODE2019_DAY01

#include "../includes/aoc.h"
#include <iostream>

class Day01 {
private:
	int calculateFuelCosts(int mass)
	{
		if (mass <= 5)
			return 0;

		return mass / 3 - 2;
	}

	int calculateFuelCostsRecursive(int mass)
	{
		if (mass <= 8)
			return 0;

		int val = mass / 3 - 2;
		return val + calculateFuelCostsRecursive(val);
	}

	std::vector<std::string> inputs;

public:
	Day01()
	{
		inputs = util::readFileLines("..\\inputs\\2019\\input_1.txt");
	}

	int64_t run()
	{
		std::vector<int> masses = util::ConvertToInt(inputs);
		int totalMass_recursive = 0;
		int totalMass_normal = 0;

		util::Timer myTime;
		myTime.start();
        		
		for (uint32_t index = 0; index < masses.size(); ++index)
		{
			totalMass_normal += calculateFuelCosts(masses[index]);
			totalMass_recursive += calculateFuelCostsRecursive(masses[index]);
		}

		int64_t time = myTime.usPassed();

		std::cout << "Day 01 - Part 1: " << totalMass_normal << std::endl
				  << "Day 01 - Part 2: " << totalMass_recursive << std::endl;

		return time;
	}
};

#endif  // ADVENTOFCODE2019_DAY01