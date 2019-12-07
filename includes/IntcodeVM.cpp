#include "IntcodeVM.h"
#include <chrono>
#include <thread>

bool IntcodeVM::analyzeOpcode(int opcode, int modePos1, int modePos2, int modePos3, std::vector<int64_t>& commands, int64_t& index, std::vector<int64_t>& _input, int& inputIndex)
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
		if (inputIndex >= _input.size())
		{
			return false;
		}
		commands[commands[index + 1]] = _input[inputIndex++];
		index += 2;
	}

	if (opcode == operationCodes::opcode_output)
	{
		outputsAdded.push_back(commands[commands[index + 1]]);
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
			// new output was generated. Save current settings, and go to next VM
			status.index = index;
			return outputsAdded;
		}
	}

	return outputsAdded;
}