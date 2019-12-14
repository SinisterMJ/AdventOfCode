#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <regex>
#include <map>
#include <thread>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include <inttypes.h>

typedef std::pair<std::string, int64_t> Material;
typedef std::map<std::string, std::pair<int64_t, std::vector<Material>>> Element;

bool checkPath(std::string input, std::string superior, Element& reactions)
{
	if (input == "ORE")
		return false;

	if (input == superior)
		return true;

	auto elem = reactions[superior];

	for (auto source : elem.second)
	{
		if (checkPath(input, source.first, reactions))
			return true;
	}

	return false;	
}

int64_t calcOreUsage(Element& reactions, int64_t count)
{
	bool allOres = false;

	std::map<std::string, int64_t> requiredMats;
	std::map<std::string, int64_t> warehouse = { };
	std::map<std::string, int64_t> temp;

	requiredMats["FUEL"] = count;
	
	while (!(requiredMats.size() == 1 && requiredMats["ORE"] != 0))
	{
		temp.clear();
		
		for (auto elem : requiredMats)
		{
			bool foundInMap = false;
			
			// Check if the current element is in the requirements of the others
			for (auto check : requiredMats)
			{
				if (check.first == elem.first)
					continue;

				if (foundInMap = checkPath(elem.first, check.first, reactions))
				{
					temp[elem.first] += elem.second;
					bool foundInMap = false;
					break;
				}
			}

			if (foundInMap)
				continue;

			if (elem.first != "ORE")
			{
				std::string name = elem.first;
				int64_t quantity = std::max<int64_t>(0, elem.second - warehouse[elem.first]);
				auto input = reactions[elem.first];
				int64_t outputQuantity = input.first;
				int64_t multiple = std::ceil(static_cast<double>(quantity) / outputQuantity);
				
				warehouse[elem.first] = multiple * outputQuantity - quantity;

				for (auto outputElem : reactions[elem.first].second)
				{
					temp[outputElem.first] += multiple * outputElem.second;
				}
			}

			if (elem.first == "ORE")
			{
				temp[elem.first] += elem.second;
			}
		}

		requiredMats.swap(temp);
	}

	return requiredMats["ORE"];
}


int64_t calcFuelOutcome(Element& reactions, int64_t inputOre)
{
	int64_t lowerEstimate = inputOre / calcOreUsage(reactions, 1);
	int64_t higherEstimate = 1.1 * lowerEstimate;

	while (calcOreUsage(reactions, higherEstimate) < inputOre)
	{
		lowerEstimate = higherEstimate;
		higherEstimate *= 1.05;
	}

	int64_t mid = (lowerEstimate + higherEstimate) / 2;
	int64_t resMid = 0;

	while (mid != lowerEstimate && mid != higherEstimate)
	{
		resMid = calcOreUsage(reactions, mid);
		if (resMid > inputOre)
		{
			higherEstimate = mid;
		}

		if (resMid < inputOre)
		{
			lowerEstimate = mid;
		}

		if (resMid == inputOre)
			return mid;
		mid = (lowerEstimate + higherEstimate) / 2;
	}

	return mid;
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFileLines("..\\inputs\\input_2019_14.txt");
	
	Element reactions;

	for (auto elem : input)
	{
		std::string output = elem.substr(elem.find("=>") + 3);
		std::string input = elem.substr(0, elem.find("=>"));
		auto inputs = util::split(input, ',');
		for (auto& str : inputs)
			if (str[0] == ' ')
				str = str.substr(1);

		auto out = util::split(output, ' ');
		reactions[out[1]] = std::make_pair(std::stoi(out[0]), std::vector<std::pair<std::string, int64_t>>());

		for (auto str : inputs)
		{
			auto in = util::split(str, ' ');
			reactions[out[1]].second.push_back(std::make_pair(in[1], std::stoi(in[0])));
		}
	}

	int64_t result1 = calcOreUsage(reactions, 1);
	int64_t result2 = calcFuelOutcome(reactions, 1000000000000);
	   

	std::cout << "Part 1: " << result1 << std::endl;
	std::cout << "Part 2: " << result2 << std::endl;
	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}