#ifndef ADVENTOFCODE2016_DAY19
#define ADVENTOFCODE2016_DAY19

#include "../includes/aoc.h"
#include <set>

class Day19 {
private:
	std::vector<std::string> inputLines;
	
	struct Reaction {
		std::string input;
		std::string output;
	};

	std::vector<Reaction> reactionList;
	std::string molecule;

	void buildReactions()
	{
		for (auto& line : inputLines)
		{
			if (line.find(" => ") != std::string::npos)
			{
				auto pos = line.find(" => ");
				Reaction entry;
				entry.input = line.substr(0, pos);
				entry.output = line.substr(pos + 4);
				reactionList.push_back(entry);
			}
		}

		molecule = inputLines.back();
	}

	int64_t part1()
	{
		std::set<std::string> uniqueOutcomes;

		for (int position = 0; position < molecule.size(); ++position)
		{
			for (auto& entry : reactionList)
			{
				if (molecule.substr(position, entry.input.size()) == entry.input)
				{
					std::string copy = molecule.substr(0, position) + entry.output + molecule.substr(position + entry.input.size());
					uniqueOutcomes.insert(copy);
				}
			}
		}

		return uniqueOutcomes.size();
	}

	int64_t countUpper(std::string str)
	{
		int upper = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				upper++;
		}
		
		return upper;
	}

	int64_t count(std::string input, std::string search)
	{
		int64_t pos = 0;
		int64_t count = 0;
		while ((pos = input.find(search, pos)) != std::string::npos)
		{
			count++;
			pos += search.length();
		}

		return count;
	}

	int64_t part2()
	{
		int64_t countRN = count(molecule, "Rn");
		int64_t countAR = count(molecule, "Ar");
		int64_t countY = count(molecule, "Y");
		int64_t countUp = countUpper(molecule);

		return countUp - countRN - countAR - 2 * countY - 1;
	}

public:
	Day19()
	{
		inputLines = util::readFileLines("..\\inputs\\2016\\input_19.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		buildReactions();

		int64_t result1 = part1();
		int64_t result2 = part2();

		std::cout << "Day 19 - Part 1: " << result1 << std::endl;
		std::cout << "Day 19 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY19