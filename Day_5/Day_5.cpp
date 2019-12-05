// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
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
	for (uint32_t index = 0; index < commands.size();)
	{
		int opcode = commands[index] % 100;
		int param_1 = (commands[index] / 100) % 10;
		int param_2 = (commands[index] / 1000) % 10;
		int param_3 = (commands[index] / 10000) % 10;

		int param_1_val, param_2_val, param_3_val;

		if (param_1 == 0)
			param_1_val = commands[commands[index + 1]];
		if (param_1 == 1)
			param_1_val = commands[index + 1];
		
		if (param_2 == 0)
			param_2_val = commands[commands[index + 2]];
		if (param_2 == 1)
			param_2_val = commands[index + 2];

		if (param_3 == 0)
			param_3_val = commands[commands[index + 3]];
		if (param_3 == 1)
			param_3_val = commands[index + 3];

		switch (commands[index]) {
		case 1:
			commands[param_3_val] = param_1_val + param_2_val;
			index += 4;
			break;
		case 2:
			commands[param_3_val] = param_1_val * param_2_val;
			index += 4;
			break;
		case 3:
			commands[param_1_val] = 1;
			index += 2;
			break;
		case 4:
			std::cout << "Opcode 4: value=" << param_1_val;
			index += 2;
			break;
		case 99:
			return commands[0];
			break;
		default:
			//return -1;
		}
	}
	return -1;
}

int main()
{
	std::string inputString = util::readFile("..\\input_2019_5.txt");
	std::vector<int> commands = splitInt(inputString, ',');
	commands.resize(10000);
	int value_1 = runCommands(commands);

	std::cout << "Solution on AoC Day 5 Part 1: " << value_1 << std::endl;

	getchar();
	return 0;
}