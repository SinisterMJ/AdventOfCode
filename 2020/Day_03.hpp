#ifndef ADVENTOFCODE2020_DAY03
#define ADVENTOFCODE2020_DAY03

#include "../includes/aoc.h"

class Day03 {
private:
	
	std::vector<std::string> inputs;
    std::string input;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\2020\\input_3.txt");
        input = util::readFile("..\\inputs\\2020\\input_3.txt");
	}
        
    int64_t trees_hit(std::pair<int, int> slope) 
    {
        int line = 0; int col = 0;
        int trees = 0;

        while (line < inputs.size())
        {
            trees += (inputs[line][col % inputs[line].length()] == '#');
            col += slope.first;
            line += slope.second;
        }

        return trees;
    }

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        std::vector<std::pair<int32_t, int32_t>> vPaths = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

        int64_t result_1 = trees_hit(vPaths[1]);
        int64_t result_2 = 1;
        
        for (auto elem : vPaths)
            result_2 *= trees_hit(elem);
        
        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY03