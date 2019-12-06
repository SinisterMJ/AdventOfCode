// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

int main()
{
	util::Timer myTime;
	myTime.start();
	auto inputString = util::readFileLines("..\\input_2019_7.txt");



	std::cout << "Part 1: " << 0 << std::endl;
	std::cout << "Part 2: " << 0 << std::endl;

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	system("pause");
	return 0;
}