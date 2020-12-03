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
		inputs = util::readFileLines("..\\inputs\\input_2020_3.txt");
        input = util::readFile("..\\inputs\\input_2020_3.txt");
	}
        
    int64_t trees_hit(int x, int y) 
    {
        int line = 0; int col = 0;
        int trees = 0;

        while (line < inputs.size())
        {
            trees += (inputs[line][col % inputs[line].length()] == '#');
            line += y;
            col += x;
        }

        return trees;
    }

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int64_t result_1 = trees_hit(3, 1);
        int64_t result_2 = trees_hit(1,1) * trees_hit(3, 1) * trees_hit(5, 1) * trees_hit(7, 1) * trees_hit(1, 2);
        
        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY03