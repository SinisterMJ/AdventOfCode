#ifndef ADVENTOFCODE2015_DAY25
#define ADVENTOFCODE2015_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
	int64_t run_code_sequence(int row, int column)
	{
		int64_t val = 20151125;
		int64_t mul = 252533;
		int64_t mod = 33554393;

		int32_t curr_row = 1;
		int32_t curr_col = 1;

		while (curr_row != row || curr_col != column)
		{
			curr_row -= 1;
			curr_col += 1;

			if (curr_row == 0)
			{
				curr_row = curr_col;
				curr_col = 1;
			}

			val = (val * mul) % mod;
		}

		return val;
	}

public:
	Day25()
	{
		
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		int64_t result1 = run_code_sequence(2947, 3029);

		std::cout << "Day 25 - Part 1: " << result1 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY25