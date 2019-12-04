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

    std::reverse(result.begin(), result.end());

	return result;
}

bool validPassword_part1(std::vector<int> digits)
{
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

bool validPassword_part2(std::vector<int> digits)
{
	bool foundDouble = false;
	for (int index = 1; index < digits.size(); ++index)
	{
		if (digits[index] < digits[index - 1])
			return false;

		if (digits[index] == digits[index - 1])
		{
			if (index - 2 >= 0 && digits[index] == digits[index - 2])
				continue;

			if (index + 1 < digits.size() && digits[index] == digits[index + 1])
				continue;

			foundDouble = true;
		}
	}

	return foundDouble;
}

int main()
{
    util::Timer myTime;
    myTime.start();
    std::vector<std::string> input = util::readFileLines("..\\input_2019_4.txt", '-');
	int lower = std::stoi(input[0]);
	int higher = std::stoi(input[1]);
	
	int count_part1 = 0;
	int count_part2 = 0;
	for (int index = lower; index <= higher; ++index)
	{
        std::vector<int> input = digitsFromInt(index);
        if (validPassword_part1(input))
        {
            count_part1++;
            count_part2 += validPassword_part2(input);  // Part 2 is a strict subset of part 1
        }		
	}

	std::cout << "Part 1: " << count_part1 << std::endl;
	std::cout << "Part 2: " << count_part2 << std::endl;
    std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();

    return 0;
}