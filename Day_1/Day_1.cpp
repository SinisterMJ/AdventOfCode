// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../includes/aoc.h"
#include <iostream>

int calculateFuelCosts(int mass)
{
	if (mass <= 5)
		return 0;

	return mass / 3 - 2;
}

int calculateFuelCostsRecursive(int mass)
{
	if (mass <= 5)
		return 0;
	
	int val = mass / 3 - 2;
	return val + calculateFuelCostsRecursive(val);
}

int main()
{
	std::vector<std::string> inputs = util::readFileLines("..\\inputs\\input_2019_1.txt");
	std::vector<int> masses;
	for (auto elem: inputs)
	{
		masses.push_back(std::stoi(elem));
	}

	int totalMass_recursive = 0;
	int totalMass_normal = 0;

	for (uint32_t index = 0; index < masses.size(); ++index)
	{
		// 1st question, uncomment following line
		totalMass_normal += calculateFuelCosts(masses[index]);

		// Second question, uncomment following line
		totalMass_recursive += calculateFuelCostsRecursive(masses[index]);
	}

	std::cout << "Total fuel mass    (normal): " << totalMass_normal << std::endl;
	std::cout << "Total fuel mass (recursive): " << totalMass_recursive << std::endl;
	getchar();
	return 0;
}