#ifndef ADVENTOFCODE_ACCUMULATORVM
#define ADVENTOFCODE_ACCUMULATORVM

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stdint.h>

class AccumulatorVM
{
public:
    enum operationCodes {
        opcode_acc = 0,
        opcode_nop,
        opcode_jump
    };

    struct Command {
        operationCodes com;
        int64_t value;
    };

private:
    int64_t index;
    int64_t accumulator;
    std::set<int64_t> visited;
    
    std::vector<Command> commands;
    bool terminated;

public:
    AccumulatorVM() : index(0), accumulator(0), terminated(false) { }
    
    AccumulatorVM& initializeCommands(std::vector<std::string> _commands)
    {
        commands.clear();
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

            commands.emplace_back(temp);
        }

        return *this;
    }

    void reset() {
        index = 0;
        accumulator = 0;
        terminated = 0;
        visited.clear();
    }

    std::vector<Command>& getCommands() {
        return commands;
    }
    
    int64_t runCommands();
    bool hasTerminated() { return terminated; }
};

#endif  // ADVENTOFCODE_ACCUMULATORVM