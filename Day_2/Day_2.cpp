// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../includes/aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<int> splitInt(const std::string &s, char delim) {
	std::vector<int> elems;
	std::stringstream ss(s);
	std::string number;
	while (std::getline(ss, number, delim)) {
		elems.push_back(std::stoi(number));
	}
	return elems;
}

int runCommands(std::vector<int> commands)
{
	for (uint32_t index = 0; index < commands.size(); index += 4)
	{
		switch (commands[index]) {
		case 1:
			commands[commands[index + 3]] = commands[commands[index + 1]] + commands[commands[index + 2]];
			break;
		case 2:
			commands[commands[index + 3]] = commands[commands[index + 1]] * commands[commands[index + 2]];
			break;
		case 99:
			return commands[0];
			break;
		default:
			return -1;
		}
	}
	return -1;
}

int main()
{
	std::string inputString = util::readFile("..\\inputs\\input_2019_2.txt");
	std::vector<int> commands = splitInt(inputString, ',');
	
	commands[1] = 12;
	commands[2] = 2;
	int value_1 = runCommands(commands);

	std::cout << "Solution on AoC Part 1: " << value_1 << std::endl;

	
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			commands[1] = i;
			commands[2] = j;
			int value = runCommands(commands);
 			if (value == 19690720)
			{
				std::cout << "Valid solution. i = " << i << ", j = " << j << std::endl;
				std::cout << "Solution on AoC Part 2: " << i * 100 + j << std::endl;
				goto solution_found;
			}
		}
	}

solution_found:
	getchar();
	return 0;
}