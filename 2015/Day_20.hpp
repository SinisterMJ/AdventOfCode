#ifndef ADVENTOFCODE2015_DAY20
#define ADVENTOFCODE2015_DAY20

#include "../includes/aoc.h"

class Day20 {
private:
	int64_t input{ 33100000 };
	std::vector<int64_t> primes;

	int64_t part1()
	{
		int64_t house = 1;
		while (true)
		{
			int64_t value = 0;
			int searchMax = static_cast<int>(std::sqrt(house));
			for (int64_t index = 1; index <= searchMax; ++index)
			{
				if (house % index == 0)
				{
					value += 10 * index;
					if (index != (house / index))
						value += 10 * (house / index);
				}
			}

			if (value >= input)
				return house;

			house++;
		}
	}

	int64_t part2()
	{
		int64_t house = 1;
		while (true)
		{
			int64_t value = 0;
			int searchMax = static_cast<int>(std::sqrt(house));
			for (int64_t index = 1; index <= searchMax; ++index)
			{
				if (house % index == 0)
				{
					if (index <= 50)
						value += 11 * (house / index);

					if (index != (house / index))
					{
						if ((house / index) <= 50)
							value += 11 * index;
					}
				}
			}

			if (value >= input)
				return house;

			house++;
		}
	}

public:
	Day20()
	{
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		int64_t result1 = part1();
		int64_t result2 = part2();

		std::cout << "Day 20 - Part 1: " << result1 << std::endl;
		std::cout << "Day 20 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY20
