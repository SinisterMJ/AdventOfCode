// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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