// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
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
    util::Timer myTime;
    myTime.start();

	std::string inputString = util::readFile("..\\inputs\\input_2019_2.txt");
	std::vector<int64_t> commands = util::splitInt64(inputString, ',');
	
	commands[1] = 12;
	commands[2] = 2;
    {
        IntcodeVM vm;
        vm.initializeCommands(commands);
        vm.runCommands();
        std::cout << "Solution on AoC Part 1: " << vm.getFirstCommand() << std::endl;
    }
	
    {
        for (int i = 0; i < 100; ++i)
        {
            commands[1] = i;
            for (int j = 0; j < 100; ++j)
            {
                commands[2] = j;
                IntcodeVM vm;
                vm.initializeCommands(commands);
                vm.runCommands();

                if (vm.getFirstCommand() == 19690720)
                {
                    std::cout << "Solution on AoC Part 2: " << i * 100 + j << std::endl;
                    goto solution_found;
                }
            }
        }
    }

solution_found:
    std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}