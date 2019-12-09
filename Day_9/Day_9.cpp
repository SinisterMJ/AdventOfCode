#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdint.h>

int main()
{
	util::Timer myTime;
	myTime.start();
	std::string inputString = util::readFile("..\\inputs\\input_2019_9.txt");
	//inputString = "104,1125899906842624,99";
	std::vector<int64_t> commands = util::splitInt64(inputString, ',');
	IntcodeVM vm1;
	vm1.initializeCommands(commands);
	auto test = vm1.runCommands();

	
	IntcodeVM vm2;
	
	std::cout << "Time taken: " << myTime.msPassed() << " [ms]" << std::endl;
	getchar();
	return 0;
}