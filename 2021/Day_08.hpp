#ifndef ADVENTOFCODE2021_DAY08
#define ADVENTOFCODE2021_DAY08

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
        AccumulatorVM accvm;
        accvm.initializeCommands(inputVec);

        for (int index = 0; index < inputVec.size(); ++index)
        {
            auto& commands = accvm.getCommands();
            
            if (commands[index].com == AccumulatorVM::opcode_acc)
                continue;

            if (commands[index].com == AccumulatorVM::opcode_nop) {
                commands[index].com = AccumulatorVM::opcode_jump;
            }
            else {
                if (commands[index].com == AccumulatorVM::opcode_jump) {
                    commands[index].com = AccumulatorVM::opcode_nop;
                }
            }

            auto resultVM = accvm.runCommands();
            bool term = accvm.hasTerminated();

            if (commands[index].com == AccumulatorVM::opcode_nop) {
                commands[index].com = AccumulatorVM::opcode_jump;
            }
            else {
                if (commands[index].com == AccumulatorVM::opcode_jump) {
                    commands[index].com = AccumulatorVM::opcode_nop;
                }
            }

            if (term)
                return resultVM;

            accvm.reset();
        }

        return -1;
    }

public:
	Day08()
	{
        inputString = util::readFile("..\\inputs\\2021\\input_8.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_8.txt", '\n', true);
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

#endif  // ADVENTOFCODE2021_DAY08
