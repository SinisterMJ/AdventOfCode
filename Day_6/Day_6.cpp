// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

std::string center = "COM";

int getOrbits(std::map<std::string, std::string>& input, std::string id)
{
	if (id == center)
		return 0;

	return 1 + getOrbits(input, input[id]);
}

int getTotalOrbits(std::map<std::string, std::string>& input)
{
	int totalOrbits = 0;
	for (auto elem : input)
	{
		totalOrbits += getOrbits(input, elem.first);
	}

	return totalOrbits;
}

int findLengthBetweenOrbits(std::map<std::string, std::string>& input, std::string start, std::string end)
{
	std::string current = start;
	
	std::vector<std::string> path1;
	std::vector<std::string> path2;

	while (current != "COM")
	{
		path1.push_back(input[current]);
		current = input[current];
	}

	current = end;

	while (current != "COM")
	{
		path2.push_back(input[current]);
		current = input[current];
	}

	int steps = 0;

	for (int i = 0; i < path1.size(); ++i)
	{
		for (int j = 0; j < path2.size(); ++j)
		{
			if (path2[j] == path1[i])
			{
				return i + j;
			}
		}
	}
}

int main()
{
	util::Timer myTime;
	myTime.start();
	std::vector<std::string> inputString = util::readFileLines("..\\input_2019_6.txt");
	
	std::map<std::string, std::string> orbits;
	for (auto elem : inputString)
	{
		std::vector<std::string> list = util::split(elem, ')');
		orbits[list[1]] = list[0];
	}

	

	//std::cout << "Part 1: " << getTotalOrbits(orbits) << std::endl;
	std::cout << "Part 2: " << findLengthBetweenOrbits(orbits, "YOU", "SAN") << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}