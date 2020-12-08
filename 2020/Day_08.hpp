#ifndef ADVENTOFCODE2020_DAY08
#define ADVENTOFCODE2020_DAY08

#include "../includes/aoc.h"
#include "../includes/AccumulatorVM.h"

class Day08 {
private:
	std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1() {
        AccumulatorVM accvm;
        return accvm.initializeCommands(inputVec).runCommands();
    }

    int64_t part2()
    {
        for (int index = 0; index < inputVec.size(); ++index)
        {
            AccumulatorVM accvm;
            if (inputVec[index].find("nop") != std::string::npos)
            {
                inputVec[index] = std::regex_replace(inputVec[index], std::regex("nop"), "jmp");
            } 
            else if (inputVec[index].find("jmp") != std::string::npos)
            {
                inputVec[index] = std::regex_replace(inputVec[index], std::regex("jmp"), "nop");
            }
            else {
                continue;
            }
            
            auto resultVM = accvm.initializeCommands(inputVec).runCommands();
            bool term = accvm.hasTerminated();

            // change it back
            if (inputVec[index].find("nop") != std::string::npos)
            {
                inputVec[index] = std::regex_replace(inputVec[index], std::regex("nop"), "jmp");
            }
            else if (inputVec[index].find("jmp") != std::string::npos)
            {
                inputVec[index] = std::regex_replace(inputVec[index], std::regex("jmp"), "nop");
            }

            if (term)
                return resultVM;
        }

        return -1;
    }

public:
	Day08()
	{
        inputString = util::readFile("..\\inputs\\input_2020_8.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_8.txt", '\n', true);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY08
