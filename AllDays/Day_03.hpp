#ifndef ADVENTOFCODE2019_DAY03
#define ADVENTOFCODE2019_DAY03

#include "../includes/aoc.h"
#include <map>
#include <iostream>

class Day03 {
private:
	class Wire {
	private:
		std::map<v2, int> passedPointsLength;

	public:
		Wire(std::string path)
		{
			std::vector<std::string> directions = util::split(path, ',');
			v2 start;
			int totalSteps = 0;

			for (uint32_t index = 0; index < directions.size(); ++index)
			{
				v2 direction;
				if (directions[index].at(0) == 'L')
					direction.x = -1;

				if (directions[index].at(0) == 'R')
					direction.x = 1;

				if (directions[index].at(0) == 'U')
					direction.y = 1;

				if (directions[index].at(0) == 'D')
					direction.y = -1;

				int length = std::stoi(directions[index].substr(1));

				for (int run = 0; run < length; ++run, ++totalSteps)
				{
					start = start + direction;
					if (passedPointsLength.find(start) == passedPointsLength.end())
					{
						passedPointsLength[start] = totalSteps;
					}
				}
			}
		}

		int shortestDistance(std::map<v2, int>& comparison)
		{
			int minDistance = std::numeric_limits<int>::max();
			for (auto elem : comparison)
			{
				if (passedPointsLength.find(elem.first) != passedPointsLength.end())
				{
					int distance = std::abs(elem.first.x) + std::abs(elem.first.y);
					if (distance < minDistance)
						minDistance = distance;
				}
			}

			return minDistance;
		}

		int shortestSteps(std::map<v2, int>& comparison)
		{
			int minDistance = std::numeric_limits<int>::max();
			for (auto elem : comparison)
			{
				if (passedPointsLength.find(elem.first) != passedPointsLength.end())
				{
					int distance = elem.second + passedPointsLength[elem.first] + 2;
					if (distance < minDistance)
						minDistance = distance;
				}
			}

			return minDistance;
		}

		std::map<v2, int>& getPoints()
		{
			return passedPointsLength;
		}
	};
	std::vector<std::string> inputs;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\input_2019_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		Wire A(inputs[0]);
		Wire B(inputs[1]);
		int distance = A.shortestDistance(B.getPoints());
		int steps = A.shortestSteps(B.getPoints());

		std::cout << "Day 03 - Part 1: " << distance << std::endl
				  << "Day 03 - Part 2: " << steps << std::endl;
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY03