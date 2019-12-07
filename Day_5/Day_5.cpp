// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../includes/aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum operationCodes {
    opcode_add = 1,
    opcode_mul,
    opcode_input,
    opcode_output,
    opcode_jumptrue,
    opcode_jumpfalse,
    opcode_lessthan,
    opcode_equals,
    opcode_terminate = 99
};

std::vector<int> splitInt(const std::string &s, char delim) {
	std::vector<int> elems;
	std::stringstream ss(s);
	std::string number;
	while (std::getline(ss, number, delim)) {
		elems.push_back(std::stoi(number));
	}
	return elems;
}

#pragma region opcodes
void analyzeOpcode(int opcode, int modePos1, int modePos2, int modePos3, std::vector<int>& commands, uint32_t& index, int& _input, int& output)
{
    if (opcode == operationCodes::opcode_add)
    {
        commands[commands[index + 3]] =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]) +
            (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
        index += 4;
    }

    if (opcode == operationCodes::opcode_mul)
    {
        commands[commands[index + 3]] =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]) *
            (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
        index += 4;
    }

    if (opcode == operationCodes::opcode_jumptrue)
    {
        auto& param_1_val =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]);
        if (param_1_val == 0)
        {
            index += 3;
        }
        else
        {
            auto& param_2_val =
                (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
            index = param_2_val;
        }
    }

    if (opcode == operationCodes::opcode_jumpfalse)
    {
        auto& param_1_val =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]);
        if (param_1_val != 0)
        {
            index += 3;
        }
        else
        {
            auto& param_2_val =
                (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
            index = param_2_val;
        }
    }

    if (opcode == operationCodes::opcode_lessthan)
    {
        auto& param_1_val =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]);
        auto& param_2_val =
            (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
        commands[commands[index + 3]] = (param_1_val < param_2_val ? 1 : 0);
        index += 4;
    }

    if (opcode == operationCodes::opcode_equals)
    {
        auto& param_1_val =
            (modePos1 == 0 ? commands[commands[index + 1]] : commands[index + 1]);
        auto& param_2_val =
            (modePos2 == 0 ? commands[commands[index + 2]] : commands[index + 2]);
        commands[commands[index + 3]] = (param_1_val == param_2_val ? 1 : 0);
        index += 4;
    }

    if (opcode == operationCodes::opcode_input)
    {
        commands[commands[index + 1]] = _input;
        index += 2;
    }

    if (opcode == operationCodes::opcode_output)
    {
        if (commands[commands[index + 1]] != 0)
            output = commands[commands[index + 1]];
        index += 2;
    }
}
#pragma endregion

int runCommands(std::vector<int> commands, int _input)
{
    std::vector<int> outputs;
    int output = -1;
	for (uint32_t index = 0; index < commands.size();)
	{
		int opcode = commands[index] % 100;
		int param_1 = (commands[index] / 100) % 10;
		int param_2 = (commands[index] / 1000) % 10;
		int param_3 = (commands[index] / 10000) % 10;

        if (opcode == operationCodes::opcode_terminate)
            return output;

        analyzeOpcode(opcode, param_1, param_2, param_3, commands, index, _input, output);
	}

	return -1;
}

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\inputs\\input_2019_5.txt");
	std::vector<int> commands = splitInt(inputString, ',');
	
    int value_part1 = runCommands(commands, 1);
    std::cout << "Solution on AoC Day 5 Part 1: " << value_part1 << std::endl;
	
    int value_part2 = runCommands(commands, 5);
    std::cout << "Solution on AoC Day 5 Part 2: " << value_part2 << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}