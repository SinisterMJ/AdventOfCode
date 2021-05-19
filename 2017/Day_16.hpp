#ifndef ADVENTOFCODE2017_DAY16
#define ADVENTOFCODE2017_DAY16

#include <map>

#include "../includes/aoc.h"
#include <regex>

class Day16 {
private:

	std::map<int32_t, std::map<std::string, int32_t>> allSues;

	int64_t part1(std::map<std::string, int32_t> sue)
	{
		std::regex reg("Sue ([0-9]+): (\\S+): ([0-9]+), (\\S+): ([0-9]+), (\\S+): ([0-9]+)");
		std::smatch sue_match;

		for (auto line : inputLines)
		{
			std::regex_search(line, sue_match, reg);

			std::map<std::string, int32_t> entry;

			entry[sue_match[2]] = std::stoi(sue_match[3]);
			entry[sue_match[4]] = std::stoi(sue_match[5]);
			entry[sue_match[6]] = std::stoi(sue_match[7]);

			allSues[std::stoi(sue_match[1])] = entry;
		}

		for (auto& entry : allSues)
		{
			bool match = true;

			for (auto& key : sue)
			{
				if (entry.second.find(key.first) != entry.second.end())
				{
					match &= (entry.second[key.first] == key.second);
				}
			}
			
			if (match)
				return entry.first;
		}

		return 0;
	}

	int64_t part2(std::map<std::string, int32_t> sue)
	{
		for (auto& entry : allSues)
		{
			bool match = true;

			for (auto& key : sue)
			{
				if (entry.second.find(key.first) != entry.second.end())
				{
					if (key.first != "cats" && key.first != "trees" && key.first != "pomerians" && key.first != "goldfish")
						match &= (entry.second[key.first] == key.second);
					else
					{
						if (key.first == "cats" || key.first == "trees")
						{
							match &= (entry.second[key.first] > key.second);
						}
						else
						{
							match &= (entry.second[key.first] < key.second);
						}
					}
				}
			}

			if (match)
				return entry.first;
		}

		return 0;
	}

	std::string inputString;
	std::vector<std::string> inputLines;
public:
	Day16()
	{
		inputString = util::readFile("..\\inputs\\2017\\input_16.txt");
		inputLines = util::readFileLines("..\\inputs\\2017\\input_16.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::map<std::string, int32_t> present;

		present["children"] = 3;
		present["cats"] = 7;
		present["samoyeds"] = 2;
		present["pomeranians"] = 3;
		present["akitas"] = 0;
		present["vizslas"] = 0;
		present["goldfish"] = 5;
		present["trees"] = 3;
		present["cars"] = 2;
		present["perfumes"] = 1;

		int64_t result1 = part1(present);
		int64_t result2 = part2(present);

		std::cout << "Day 16 - Part 1: " << result1 << std::endl
				  << "Day 16 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY16