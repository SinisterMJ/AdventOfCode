#ifndef ADVENTOFCODE2019_DAY14
#define ADVENTOFCODE2019_DAY14

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

#include <map>
#include <algorithm>


class Day14 {
private:
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
		int64_t totalOre = 0;

		while (requiredMats.size() > 0)
		{
			temp.clear();

			for (auto elem : requiredMats)
			{
				std::string name = elem.first;
				int64_t quantity = std::max<int64_t>(0, elem.second - warehouse[elem.first]);
				auto input = reactions[elem.first];
				int64_t outputQuantity = input.first;
				int64_t multiple = static_cast<int64_t>(std::ceil(static_cast<double>(quantity) / outputQuantity));

				warehouse[elem.first] += multiple * outputQuantity - elem.second;

				for (auto outputElem : reactions[elem.first].second)
				{
					if (outputElem.first == "ORE")
						totalOre += multiple * outputElem.second;
					else
						temp[outputElem.first] += multiple * outputElem.second;
				}
			}

			requiredMats.swap(temp);
		}

		return totalOre;
	}


	int64_t calcFuelOutcome(Element& reactions, int64_t inputOre)
	{
		int64_t lowerEstimate = inputOre / calcOreUsage(reactions, 1);
		int64_t higherEstimate = 2 * lowerEstimate;

		while (calcOreUsage(reactions, higherEstimate) < inputOre)
		{
			lowerEstimate = higherEstimate;
			higherEstimate *= 2;
		}

		int64_t mid = (lowerEstimate + higherEstimate) / 2;
		int64_t resMid = 0;

		while (lowerEstimate <= higherEstimate)
		{
			resMid = calcOreUsage(reactions, mid);
			if (resMid > inputOre)
			{
				higherEstimate = mid - 1;
			}

			if (resMid < inputOre)
			{
				lowerEstimate = mid + 1;
			}

			if (resMid == inputOre)
				return mid;

			mid = (lowerEstimate + higherEstimate) / 2;
		}

		return mid;
	}

	std::vector<std::string> input;
public:
	Day14()
	{
		input = util::readFileLines("..\\inputs\\input_2019_14.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

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


		std::cout << "Day 14 - Part 1: " << result1 << std::endl
				  << "Day 14 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY14