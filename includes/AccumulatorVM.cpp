#include "AccumulatorVM.h"
#include <chrono>
#include <thread>
#include <set>

int64_t AccumulatorVM::runCommands()
{
    for (;;)
    {
        if (visited.find(index) != visited.end() || index >= static_cast<int64_t>(commands.size()))
        {
            terminated = (index >= static_cast<int64_t>(commands.size()));
            return accumulator;
        }

        visited.insert(index);
        Command cm = commands[index];
        switch (cm.com) {
        case opcode_acc: accumulator += cm.value;
        case opcode_nop: index++; break;
        case opcode_jump: index += cm.value; break;
        default:
            ;
        }
    }
}