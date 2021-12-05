#ifndef ADVENTOFCODE2017_DAY08
#define ADVENTOFCODE2017_DAY08

#include "../includes/aoc.h"
#include <map>

class Day08 {
private:
	std::vector<std::string> inputVec;

	struct Command {
		std::string reg1;		
		int32_t increment;
		std::string reg2;
		std::string operation;
		int32_t number;
	};

	std::vector<Command> allCommands;

	void parse_commands()
	{
		for (auto& line : inputVec)
		{
			Command entry;
			auto values = util::split(line, ' ');
			entry.reg1 = values[0];
			entry.increment = std::stoi(values[2]);
			
			if (values[1] == "dec")
				entry.increment = -entry.increment;

			entry.reg2 = values[4];
			entry.operation = values[5];
			entry.number = std::stoi(values[6]);

			allCommands.push_back(entry);
		}
	}

	std::pair<int32_t, int32_t> solve()
	{
		std::map<std::string, int32_t> registers;
		int32_t foreverMax = 0;

		for (auto& cmd : allCommands)
		{
			auto value = registers[cmd.reg2];

			bool execute = false;

			if (cmd.operation == "==")
				if (value == cmd.number)
					execute = true;
			
			if (cmd.operation == "<=")
				if (value <= cmd.number)
					execute = true;

			if (cmd.operation == "<")
				if (value < cmd.number)
					execute = true;

			if (cmd.operation == ">=")
				if (value >= cmd.number)
					execute = true;

			if (cmd.operation == ">")
				if (value > cmd.number)
					execute = true;

			if (cmd.operation == "!=")
				if (value != cmd.number)
					execute = true;

			if (execute)
				registers[cmd.reg1] += cmd.increment;

			foreverMax = std::max(foreverMax, registers[cmd.reg1]);
		}

		int32_t max = 0;
		for (auto& reg : registers)
		{
			max = std::max(max, reg.second);
		}

		return std::make_pair(max, foreverMax);
	}

public:
	Day08()
	{
        inputVec = util::readFileLines("..\\inputs\\2017\\input_8.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		parse_commands();
		auto maxes = solve();
        auto result_1 = maxes.first;
        auto result_2 = maxes.second;

		std::cout << "Day 08 - Part 1: " << result_1 << std::endl
				  << "Day 08 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY08