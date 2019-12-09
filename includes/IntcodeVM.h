#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class IntcodeVM
{
private:
	enum operationCodes {
		opcode_add = 1,
		opcode_mul,
		opcode_input,
		opcode_output,
		opcode_jumptrue,
		opcode_jumpfalse,
		opcode_lessthan,
		opcode_equals,
		opcode_relativebase,
		opcode_terminate = 99
	};

	struct currentState {
		std::vector<int64_t> commands;
		int64_t index = 0;
		int32_t inputIndex = 0;
		bool terminated = false;
		int64_t relativeBase = 0;
	};

	bool analyzeOpcode(int opcode, int modePos1, int modePos2, int modePos3, std::vector<int64_t>& commands, int64_t& index, std::vector<int64_t>& _input, int& inputIndex);
	int64_t readValue(int modePos, int64_t index, std::vector<int64_t>& commands);
	int64_t readAndResize(int64_t index, std::vector<int64_t>& commands);
	void writeValue(int modePos, int64_t value, int64_t index, std::vector<int64_t>& commands);

	currentState status;
	std::vector<int64_t> inputsAdded;
	std::vector<int64_t> outputsAdded;
public:

	IntcodeVM() {}

	IntcodeVM* initializeCommands(std::vector<int64_t> _commands) {
		status.commands = _commands;
		return this;
	}

	IntcodeVM* addInput(std::vector<int64_t> in)
	{
		inputsAdded.insert(inputsAdded.end(), in.begin(), in.end());
		return this;
	}

    std::vector<int64_t> runCommands();

    int64_t getFirstCommand() { return status.commands[0]; }

	bool hasTerminated() { return status.terminated; }
};