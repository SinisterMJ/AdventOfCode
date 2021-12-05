#ifndef ADVENTOFCODE2015_DAY03
#define ADVENTOFCODE2015_DAY03

#include "../includes/aoc.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>

class Day03 {
private:
	std::string input;
public:
	Day03()
	{
		input = util::readFile("..\\inputs\\2015\\input_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        auto result_1 = 0;
        auto result_2 = 0;
        
        std::map<v2, int32_t> visited_1;
        std::map<v2, int32_t> visited_2;

        v2 start_1;
        v2 start_2[2];
        visited_1[start_1] = 1;
        visited_2[start_2[0]] = 1;

        for (int32_t index = 0; index < input.size(); ++index)
        {
            if (input[index] == '<')
            {
                start_1.x--;
                start_2[index & 0x1].x--;
            }

            if (input[index] == '>')
            {
                start_1.x++;
                start_2[index & 0x1].x++;
            }

            if (input[index] == '^')
            {
                start_1.y--;
                start_2[index & 0x1].y--;
            }

            if (input[index] == 'v')
            {
                start_1.y++;
                start_2[index & 0x1].y++;
            }

            visited_1[start_1]++;
            visited_2[start_2[index & 0x1]]++;
        }

        result_1 = visited_1.size();
        result_2 = visited_2.size();
        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << std::endl
                  << "Day 03 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2015_DAY03