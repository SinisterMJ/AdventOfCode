// Day_3.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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

	return result;
}

bool validPassword_part1(int input)
{
	std::vector<int> digits = digitsFromInt(input);
	std::reverse(digits.begin(), digits.end());
	bool foundDouble = false;
	for (int index = 1; index < digits.size(); ++index)
	{
		if (digits[index] < digits[index - 1])
			return false;

		if (digits[index] == digits[index - 1])
			foundDouble = true;
	}

	return foundDouble;
}

bool validPassword_part2(int input)
{
	std::vector<int> digits = digitsFromInt(input);
	std::reverse(digits.begin(), digits.end());
	bool foundDouble = false;
	for (int index = 1; index < digits.size(); ++index)
	{
		if (digits[index] < digits[index - 1])
			return false;

		if (digits[index] == digits[index - 1])
		{
			if (index - 2 >= 0 && digits[index] == digits[index - 2])
			{
				continue;
			}
			if (index + 1 < digits.size() && digits[index] == digits[index + 1])
			{
				continue;
			}

			foundDouble = true;
		}
	}

	return foundDouble;
}

int main()
{
	int lower = 265275;
	int higher = 781584;
	
	int count_part1 = 0;
	int count_part2 = 0;
	for (int index = lower; index <= higher; ++index)
	{
		count_part1 += validPassword_part1(index);
		count_part2 += validPassword_part2(index);
	}

	std::cout << "Part 1: " << count_part1 << std::endl;
	std::cout << "Part 2: " << count_part2 << std::endl;
	getchar();
}