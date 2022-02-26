#ifndef ADVENTOFCODE2016_DAY08
#define ADVENTOFCODE2016_DAY08

#include "../includes/aoc.h"
#include <array>

class Day08 {
private:
	std::vector<std::string> inputVec;
	std::array<std::array<bool, 50>, 6> field;

	struct command {
		bool row = false;
		bool column = false;
		bool rect = false;
		int num_one = 0;
		int num_two = 0;
	};

	std::vector<command> commands;

	void parseCommands()
	{
		for (auto elem : inputVec)
		{
			command entry;
			if (elem.find("rect") != std::string::npos)
			{
				entry.rect = true;
				auto size = util::splitInt(elem.substr(5), 'x');
				entry.num_one = size[0];
				entry.num_two = size[1];
				commands.push_back(entry);
				continue;
			}

			if (elem.find("row") != std::string::npos)
				entry.row = true;

			if (elem.find("column") != std::string::npos)
				entry.column = true;

			auto pos_eq = elem.find('=');
			auto pos_sp = elem.find(' ', pos_eq);
			entry.num_one = std::stoi(elem.substr(pos_eq + 1, pos_sp - pos_eq - 1));

			auto pos_by = elem.find("by ");
			entry.num_two = std::stoi(elem.substr(pos_by + 3));

			commands.push_back(entry);
		}
	}


	int part1()
	{
		int result = 0;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 50; j++)
				field[i][j] = false;

		for (auto cmd : commands)
		{
			std::array<std::array<bool, 50>, 6> field_temp(field);
			
			if (cmd.rect)
				for (int i = 0; i < cmd.num_two; ++i)
					for (int j = 0; j < cmd.num_one; ++j)
						field_temp[i][j] = true;
			
			if (cmd.row)
				for (int i = 0; i < 50; ++i)
					field_temp[cmd.num_one][(i + cmd.num_two) % 50] = field[cmd.num_one][i];

			if (cmd.column)
				for (int i = 0; i < 6; ++i)
					field_temp[(i + cmd.num_two) % 6][cmd.num_one] = field[i][cmd.num_one];

			field = field_temp;
		}

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 50; j++)
				result += field[i][j];

		return result;
	}

	std::string part2()
	{
		std::string result = "\n";

		for (int row = 0; row < 6; ++row)
		{
			for (int column = 0; column < 50; ++column)
			{
				if (field[row][column])
					result += '#';
				else
					result += ' ';
			}
			result += "\n";
		}

		return result;
	}

public:
	Day08()
	{
        inputVec = util::readFileLines("..\\inputs\\2016\\input_8.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
		parseCommands();

        auto result_1 = part1();
        auto result_2 = part2();

		std::cout << "Day 08 - Part 1: " << result_1 << std::endl
				  << "Day 08 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY08