#ifndef ADVENTOFCODE2016_DAY17
#define ADVENTOFCODE2016_DAY17

#include <map>

#include "../includes/aoc.h"
#include <regex>

class Day17 {
private:
	
    int64_t part1() 
    {
		int64_t total = 150;
		int64_t count = static_cast<int64_t>(std::pow(2, buckets.size()));
		int64_t totalResults = 0;

		for (int index = 0; index < count; ++index)
		{
			int64_t current = 0;
			for (int i = 0; i < buckets.size(); ++i)
			{
				if ((index >> i) & 0x1)
				{
					current += buckets[i];
				}
			}

			totalResults += (current == 150);
		}

        return totalResults;
    }

    int64_t part2() 
	{
		int64_t total = 150;
		int64_t count = static_cast<int64_t>(std::pow(2, buckets.size()));
		int64_t totalResults = 0;
		int64_t minimum = buckets.size();

		for (int index = 0; index < count; ++index)
		{
			int64_t current = 0;
			int64_t currBuckets = 0;
			for (int i = 0; i < buckets.size(); ++i)
			{
				if ((index >> i) & 0x1)
				{
					current += buckets[i];
					currBuckets++;
				}
			}

			if (current == 150)
			{
				if (currBuckets < minimum)
				{
					minimum = currBuckets;
					totalResults = 0;
				}

				totalResults += ((current == 150) && (currBuckets == minimum));
			}
		}

		return totalResults;
    }

	std::vector<std::string> inputVector;
	std::string inputString;
    std::vector<int64_t> buckets;
public:
	Day17()
	{
		inputString = util::readFile("..\\inputs\\2016\\input_17.txt");
		inputVector = util::readFileLines("..\\inputs\\2016\\input_17.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		buckets = util::ConvertToInt64(inputVector);
		
		int64_t result1 = part1();
		int64_t result2 = part2();

		std::cout << "Day 17 - Part 1: " << result1 << std::endl
				  << "Day 17 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY17