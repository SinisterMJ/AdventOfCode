// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../includes/aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

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

int main()
{
	util::Timer myTime;
	myTime.start();
	std::vector<std::string> inputString = util::readFileLines("..\\inputs\\input_2019_6.txt");
	
	std::map<std::string, std::string> orbits;
	for (auto elem : inputString)
	{
		std::vector<std::string> list = util::split(elem, ')');
		orbits[list[1]] = list[0];
	}

	std::cout << "Part 1: " << getTotalOrbits(orbits) << std::endl;
	std::cout << "Part 2: " << findLengthBetweenOrbits(orbits, "YOU", "SAN") << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}