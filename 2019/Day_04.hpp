#ifndef ADVENTOFCODE2019_DAY04
#define ADVENTOFCODE2019_DAY04

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day04 {
private:

	int getSingleDigit(int& input)
	{
		int result = input % 10;
		input /= 10;
		return result;
	}

	std::vector<int> digitsFromInt(int input)
	{
		std::vector<int> result;
		do
		{
			result.push_back(getSingleDigit(input));
		} while (input > 0);

		std::reverse(result.begin(), result.end());

		return result;
	}

	int intFromDigits(std::vector<int>& input)
	{
		int result = 0;
		for (int index = 0; index < input.size(); ++index)
		{
			result = result * 10 + input[index];
		}

		return result;
	}

	bool validPassword_part1(std::vector<int> digits, int& externalIndex)
	{
		bool foundDouble = false;
		for (int index = 1; index < digits.size(); ++index)
		{
			if (digits[index] < digits[index - 1])
			{
				for (int i = index; i < digits.size(); ++i)
				{
					digits[i] = digits[index - 1];
				}
				externalIndex = intFromDigits(digits) - 1;
				return false;
			}

			if (digits[index] == digits[index - 1])
				foundDouble = true;
		}

		return foundDouble;
	}

	bool validPassword_part2(std::vector<int> digits)
	{
		bool foundDouble = false;
		for (int32_t index = 1; index < static_cast<int32_t>(digits.size()); ++index)
		{
			if (digits[index] < digits[index - 1])
				return false;

			if (digits[index] == digits[index - 1])
			{
				if (index - 2 >= 0 && digits[index] == digits[index - 2])
					continue;

				if (index + 1 < static_cast<int32_t>(digits.size()) && digits[index] == digits[index + 1])
					continue;

				foundDouble = true;
			}
		}

		return foundDouble;
	}

	std::string inputString;
public:
	Day04()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		std::vector<std::string> input = util::readFileLines("..\\inputs\\2019\\input_4.txt", '-');
		int lower = std::stoi(input[0]);
		int higher = std::stoi(input[1]);

		int count_part1 = 0;
		int count_part2 = 0;
		for (int index = lower; index <= higher; ++index)
		{
			std::vector<int> input = digitsFromInt(index);
			if (validPassword_part1(input, index))
			{
				count_part1++;
				count_part2 += validPassword_part2(input);  // Part 2 is a strict subset of part 1
			}
		}

		std::cout << "Day 04 - Part 1: " << count_part1 << std::endl
				  << "Day 04 - Part 2: " << count_part2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY04