#ifndef ADVENTOFCODE2019_DAY06
#define ADVENTOFCODE2019_DAY06

#include "../includes/aoc.h"
#include <map>
#include "../includes/IntcodeVM.h"

class Day06 {
private:
	std::string center = "COM";

	int getOrbits(std::map<std::string, std::string>& input, std::string id, std::map<std::string, int>& orbitPassed)
	{
		if (id == center)
			return 0;

		if (orbitPassed.find(id) != orbitPassed.end())
			return orbitPassed[id];

		int result = 1 + getOrbits(input, input[id], orbitPassed);
		orbitPassed[id] = result;
		return result;
	}

	int getTotalOrbits(std::map<std::string, std::string>& input)
	{
		int totalOrbits = 0;
		std::map<std::string, int> orbitPassed;

		for (auto elem : input)
		{
			totalOrbits += getOrbits(input, elem.first, orbitPassed);
		}

		return totalOrbits;
	}

	int findLengthBetweenOrbits(std::map<std::string, std::string>& input, std::string start, std::string end)
	{
		std::string current = start;

		std::map<std::string, int> path1;
		int stepsYOU = 0;

		while (current != "COM")
		{
			path1[input[current]] = stepsYOU++;
			current = input[current];
		}

		current = end;
		int stepsSanta = -1;

		while (current != "COM")
		{
			if (path1.find(current) != path1.end())
				return path1[current] + stepsSanta;

			current = input[current];
			stepsSanta++;
		}

		return stepsSanta + stepsYOU;
	}

	std::vector<std::string> inputString;
public:
	Day06()
	{
		inputString = inputString = util::readFileLines("..\\inputs\\2019\\input_6.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		std::map<std::string, std::string> orbits;
		for (auto elem : inputString)
		{
			std::vector<std::string> list = util::split(elem, ')');
			orbits[list[1]] = list[0];
		}

		std::cout << "Day 06 - Part 1: " << getTotalOrbits(orbits) << std::endl
		          << "Day 06 - Part 2: " << findLengthBetweenOrbits(orbits, "YOU", "SAN") << std::endl;
				
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY06