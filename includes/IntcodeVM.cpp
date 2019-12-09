#include "IntcodeVM.h"
#include <chrono>
#include <thread>

int64_t IntcodeVM::readAndResize(int64_t index)
{
	if (index >= static_cast<int64_t>(status.commands.size()))
        status.commands.resize(index + 1, 0);
	
	return status.commands[index];
}

int64_t IntcodeVM::readValue(int modePos, int64_t index)
{
    int64_t address = index;
    
    if (modePos == 0)
        address = readAndResize(index);

    if (modePos == 2)
        address = readAndResize(index) + status.relativeBase;
	
    return readAndResize(address);
}

void IntcodeVM::writeValue(int modePos, int64_t value, int64_t index)
{
    int64_t address = status.commands[index] + (modePos == 2 ? status.relativeBase : 0);

    if (address >= static_cast<int64_t>(status.commands.size()))
        status.commands.resize(address + 1, 0);

    status.commands[address] = value;
}

bool IntcodeVM::analyzeOpcode(int opcode, int modePos1, int modePos2, int modePos3)
{
	if (opcode == operationCodes::opcode_add)
	{
		int64_t operand1 = readValue(modePos1, status.index + 1);
		int64_t operand2 = readValue(modePos2, status.index + 2);
		writeValue(modePos3, operand1 + operand2, status.index + 3);
        status.index += 4;
	}

	if (opcode == operationCodes::opcode_mul)
	{
		int64_t operand1 = readValue(modePos1, status.index + 1);
		int64_t operand2 = readValue(modePos2, status.index + 2);
		writeValue(modePos3, operand1 * operand2, status.index + 3);
        status.index += 4;
	}

    if (opcode == operationCodes::opcode_input)
    {
        if (status.inputIndex >= status.inputsAdded.size())
        {
            return false;
        }
        writeValue(modePos1, status.inputsAdded[status.inputIndex++], status.index + 1);
        status.index += 2;
    }

    if (opcode == operationCodes::opcode_output)
    {
        outputsAdded.push_back(readValue(modePos1, status.index + 1));
        status.index += 2;
    }

	if (opcode == operationCodes::opcode_jumptrue)
	{
		int64_t param_1_val = readValue(modePos1, status.index + 1);
		if (param_1_val == 0)
		{
            status.index += 3;
		}
		else
		{
			int64_t param_2_val = readValue(modePos2, status.index + 2);
            status.index = param_2_val;
		}
	}

	if (opcode == operationCodes::opcode_jumpfalse)
	{
		int64_t param_1_val = readValue(modePos1, status.index + 1);
		if (param_1_val != 0)
		{
            status.index += 3;
		}
		else
		{
			int64_t param_2_val = readValue(modePos2, status.index + 2);
            status.index = param_2_val;
		}
	}

	if (opcode == operationCodes::opcode_lessthan)
	{
		int64_t param_1_val = readValue(modePos1, status.index + 1);
		int64_t param_2_val = readValue(modePos2, status.index + 2);
		writeValue(modePos3, (param_1_val < param_2_val ? 1 : 0), status.index + 3);
        status.index += 4;
	}

	if (opcode == operationCodes::opcode_equals)
	{
		int64_t param_1_val = readValue(modePos1, status.index + 1);
		int64_t param_2_val = readValue(modePos2, status.index + 2);
		writeValue(modePos3, (param_1_val == param_2_val ? 1 : 0), status.index + 3);
        status.index += 4;
	}

	if (opcode == operationCodes::opcode_relativebase)
	{
		status.relativeBase += readValue(modePos1, status.index + 1);
        status.index += 2;
	}

	return true;
}

std::vector<int64_t> IntcodeVM::runCommands()
{
	outputsAdded.resize(0);
	std::vector<int64_t> outputs;
	int inputIndex = 0;
	for (; status.index < static_cast<int64_t>(status.commands.size());)
	{
		int opcode = status.commands[status.index] % 100;
		int param_1 = (status.commands[status.index] / 100) % 10;
		int param_2 = (status.commands[status.index] / 1000) % 10;
		int param_3 = (status.commands[status.index] / 10000) % 10;

		if (opcode == operationCodes::opcode_terminate)
		{
			status.terminated = true;
			break;
		}

		if (!analyzeOpcode(opcode, param_1, param_2, param_3))
		{
			// need new input. Return current results
			return outputsAdded;
		}
	}

	return outputsAdded;
}