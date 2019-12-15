#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <regex>
#include <map>
#include <thread>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include "../includes/IntcodeVM.h"
#include <inttypes.h>

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFile("..\\inputs\\input_2019_16.txt");
	
	int64_t result1 = 0;
	int64_t result2 = 0;

	std::cout << "Part 1: " << result1 << std::endl;
	std::cout << "Part 2: " << result2 << std::endl;
	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}