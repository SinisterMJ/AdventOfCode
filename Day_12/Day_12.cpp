#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFileLines("..\\inputs\\input_2019_12.txt");


	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}