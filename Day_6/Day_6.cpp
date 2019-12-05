// Day_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "../aoc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\input_2019_6.txt");
	

	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}