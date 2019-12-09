#include "IntcodeVM.h"
#include <chrono>
#include <thread>

int64_t IntcodeVM::readAndResize(int64_t index, std::vector<int64_t>& commands)
{
	if (index >= static_cast<int64_t>(commands.size()))
	{
		commands.resize(index + 1, 0);
	}

	return commands[index];
}

int64_t IntcodeVM::readValue(int modePos, int64_t index, std::vector<int64_t>& commands)
{
	if (modePos == 0)
		return readAndResize(readAndResize(index, commands), commands);
	if (modePos == 1)
		return readAndResize(index, commands);
	if (modePos == 2)
		return readAndResize(readAndResize(index, commands) + status.relativeBase, commands);

	return 0;
}

void IntcodeVM::writeValue(int modePos, int64_t value, int64_t index, std::vector<int64_t>& commands)
{
    int64_t address = commands[index] + (modePos == 2 ? status.relativeBase : 0);

    if (address >= static_cast<int64_t>(commands.size()))
        commands.resize(address + 1, 0);

    commands[address] = value;
}

bool IntcodeVM::analyzeOpcode(int opcode, int modePos1, int modePos2, int modePos3, std::vector<int64_t>& commands, int64_t& index, std::vector<int64_t>& _input, int& inputIndex)
{
	if (opcode == operationCodes::opcode_add)
	{
		int64_t operand1 = readValue(modePos1, index + 1, commands);
		int64_t operand2 = readValue(modePos2, index + 2, commands);
		writeValue(modePos3, operand1 + operand2, index + 3, commands);
		index += 4;
	}

	if (opcode == operationCodes::opcode_mul)
	{
		int64_t operand1 = readValue(modePos1, index + 1, commands);
		int64_t operand2 = readValue(modePos2, index + 2, commands);
		writeValue(modePos3, operand1 * operand2, index + 3, commands);
		index += 4;
	}

    if (opcode == operationCodes::opcode_input)
    {
        if (inputIndex >= _input.size())
        {
            return false;
        }
        writeValue(modePos1, _input[inputIndex++], index + 1, commands);
        index += 2;
    }

    if (opcode == operationCodes::opcode_output)
    {
        outputsAdded.push_back(readValue(modePos1, index + 1, commands));
        index += 2;
    }

	if (opcode == operationCodes::opcode_jumptrue)
	{
		int64_t param_1_val = readValue(modePos1, index + 1, commands);
		if (param_1_val == 0)
		{
			index += 3;
		}
		else
		{
			int64_t param_2_val = readValue(modePos2, index + 2, commands);
			index = param_2_val;
		}
	}

	if (opcode == operationCodes::opcode_jumpfalse)
	{
		int64_t param_1_val = readValue(modePos1, index + 1, commands);
		if (param_1_val != 0)
		{
			index += 3;
		}
		else
		{
			int64_t param_2_val = readValue(modePos2, index + 2, commands);
			index = param_2_val;
		}
	}

	if (opcode == operationCodes::opcode_lessthan)
	{
		int64_t param_1_val = readValue(modePos1, index + 1, commands);
		int64_t param_2_val = readValue(modePos2, index + 2, commands);
		writeValue(modePos3, (param_1_val < param_2_val ? 1 : 0), index + 3, commands);
		index += 4;
	}

	if (opcode == operationCodes::opcode_equals)
	{
		int64_t param_1_val = readValue(modePos1, index + 1, commands);
		int64_t param_2_val = readValue(modePos2, index + 2, commands);
		writeValue(modePos3, (param_1_val == param_2_val ? 1 : 0), index + 3, commands);
		index += 4;
	}

	if (opcode == operationCodes::opcode_relativebase)
	{
		status.relativeBase += readValue(modePos1, index + 1, commands);
		index += 2;
	}

	return true;
}

std::vector<int64_t> IntcodeVM::runCommands()
{
	outputsAdded.resize(0);
	std::vector<int64_t> outputs;
	int inputIndex = 0;
	for (int64_t index = status.index; index < static_cast<int64_t>(status.commands.size());)
	{
		int opcode = status.commands[index] % 100;
		int param_1 = (status.commands[index] / 100) % 10;
		int param_2 = (status.commands[index] / 1000) % 10;
		int param_3 = (status.commands[index] / 10000) % 10;

		if (opcode == operationCodes::opcode_terminate)
		{
			status.terminated = true;
			break;
		}

		if (!analyzeOpcode(opcode, param_1, param_2, param_3, status.commands, index, inputsAdded, status.inputIndex))
		{
			// need new input. Return current results
			status.index = index;
			return outputsAdded;
		}
	}

	return outputsAdded;
}