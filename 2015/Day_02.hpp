#ifndef ADVENTOFCODE2015_DAY02
#define ADVENTOFCODE2015_DAY02

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day02 {
private:
	std::vector<std::string> inputVec;
public:
	Day02()
	{
		inputVec = util::readFileLines("..\\inputs\\2015\\input_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        for (auto elem : inputVec)
        {
            std::vector<int32_t> sides = util::splitInt(elem, 'x');
            std::sort(sides.begin(), sides.end());

            result_1 += 3 * sides[0] * sides[1] + 2 * sides[0] * sides[2] + 2 * sides[1] * sides[2];
            result_2 += 2 * (sides[0] + sides[1]) + sides[0] * sides[1] * sides[2];
        }

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << std::endl
                  << "Day 02 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2015_DAY02