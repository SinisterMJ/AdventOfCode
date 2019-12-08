#include "../includes/aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdint.h>

std::string getPixel(std::vector<std::string>& inputs, int index)
{
	for (int i = 0; i < inputs.size(); ++i)
	{
		if (inputs[i].at(index) != '2')
		{
			if (inputs[i].at(index) == '0')
				return " ";
			else
				return "*";
		}
	}
	return " ";
}

int main()
{
	util::Timer myTime;
	myTime.start();
	const int height = 6;
	const int width = 25;
	std::string inputString = util::readFile("..\\inputs\\input_2019_8.txt");

	std::vector<std::string> images;
	for (int index = 0; index < inputString.length(); index += height * width)
	{
		images.push_back(inputString.substr(index, height * width));
	}

	if (images.back() == "\n")
		images.pop_back();

	std::vector<int64_t> countZero;
	std::vector<int64_t> countOne;
	std::vector<int64_t> countTwo;
	for (int index = 0; index < images.size(); ++index)
	{
		countZero.push_back(std::count(images[index].begin(), images[index].end(), '0'));
		countOne.push_back(std::count(images[index].begin(), images[index].end(), '1'));
		countTwo.push_back(std::count(images[index].begin(), images[index].end(), '2'));
	}

	int64_t minVal = std::numeric_limits<int64_t>::max();
	int64_t result = 0;
	for (int index = 0; index < images.size(); ++index)
	{
		if (countZero[index] < minVal)
		{
			minVal = countZero[index];
			result = countOne[index] * countTwo[index];
		}
	}

	std::string resultString = "";

	for (int i = 0; i < height * width; ++i)
	{
		resultString += getPixel(images, i);
		if ((i + 1) % width == 0)
			resultString += "\n";
	}

	std::cout << "Part 1: " << result << std::endl;
	std::cout << "Part 2: " << std::endl << resultString << std::endl;

	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}