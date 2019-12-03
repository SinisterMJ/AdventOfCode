// Day_3.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string number;
	while (std::getline(ss, number, delim)) {
		elems.push_back(number);
	}
	return elems;
}

class Wire {
public:
	struct Point
	{
		int x;
		int y;
	};

private:
	std::vector<Point> passedPoints;

public:
	Wire(std::string path)
	{
		std::vector<std::string> directions = split(path, ',');
		int directionUp, directionLeft;
		Point start;
		start.x = 0;
		start.y = 0;

		for (uint32_t index = 0; index < directions.size(); ++index)
		{
			if (directions[index].at(0) == 'L')
			{
				directionUp = 0;
				directionLeft = -1;
			}
			if (directions[index].at(0) == 'R')
			{
				directionUp = 0;
				directionLeft = 1;
			}
			if (directions[index].at(0) == 'U')
			{
				directionUp = 1;
				directionLeft = 0;
			}
			if (directions[index].at(0) == 'D')
			{
				directionUp = -1;
				directionLeft = 0;
			}

			int length = std::stoi(directions[index].substr(1));

			for (int run = 0; run < length; ++run)
			{
				start.x += directionLeft;
				start.y += directionUp;

				passedPoints.push_back(start);
			}
		}
	}

	int shortestDistance(std::vector<Point>& comparison)
	{
		int minDistance = std::numeric_limits<int>::max();
		for (uint32_t i = 0; i < comparison.size(); ++i)
		{
			for (uint32_t j = 0; j < passedPoints.size(); ++j)
			{
				if (passedPoints[j].x == comparison[i].x && passedPoints[j].y == comparison[i].y)
				{
					int distance = std::abs(passedPoints[j].x) + std::abs(passedPoints[j].y);
					if (distance < minDistance)
					{
						minDistance = distance;
					}
				}
			}
		}

		return minDistance;
	}

	int shortestSteps(std::vector<Point>& comparison)
	{
		uint32_t minDistance = std::numeric_limits<uint32_t>::max();
		for (uint32_t i = 0; i < comparison.size(); ++i)
		{
			if (i > minDistance)
				break;

			for (uint32_t j = 0; j < passedPoints.size(); ++j)
			{
				if (i + j >= minDistance)
					break;

				if (passedPoints[j].x == comparison[i].x && passedPoints[j].y == comparison[i].y)
				{
					uint32_t distance = i + j + 2;
					if (distance < minDistance)
					{
						minDistance = distance;
					}
				}
			}
		}

		return minDistance;
	}

	std::vector<Point>& getPoints()
	{
		return passedPoints;
	}
};


int main()
{
	std::vector<std::string> inputs = util::readFileLines("D:\\Development\\Projects\\AdventOfCode\\input_2019_3.txt");
	
	Wire A(inputs[0]);
	Wire B(inputs[1]);
	int distance = A.shortestDistance(B.getPoints());
	std::cout << "Distance: " << distance << std::endl;
	int steps = A.shortestSteps(B.getPoints());
	std::cout << "Steps: " << steps << std::endl;
	getchar();
}