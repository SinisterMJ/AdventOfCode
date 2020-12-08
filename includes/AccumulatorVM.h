#ifndef ADVENTOFCODE_ACCUMULATORVM
#define ADVENTOFCODE_ACCUMULATORVM

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class AccumulatorVM
{
private:
    enum operationCodes {
        opcode_acc = 0,
        opcode_nop,
        opcode_jump
    };

    struct Command {
        operationCodes com;
        int64_t value;
    };


    int64_t index;
    int64_t accumulator;
    
    std::vector<Command> commands;
    bool terminated;
public:
    AccumulatorVM() : index(0), accumulator(0), terminated(false) { }
    

    AccumulatorVM& initializeCommands(std::vector<std::string> _commands)
    {
        for (auto elem : _commands)
        {
            std::string first = elem.substr(0, elem.find(' '));
            std::string second = elem.substr(elem.find(' ') + 1);
            
            Command temp;
            if (first == "acc")
                temp.com = opcode_acc;
            if (first == "nop")
                temp.com = opcode_nop;
            if (first == "jmp")
                temp.com = opcode_jump;
                        
            temp.value = std::stoll(second);

            commands.push_back(temp);
        }

        return *this;
    }
    
    int64_t runCommands();
    bool hasTerminated() { return terminated; }
};

#endif  // ADVENTOFCODE_ACCUMULATORVM