#ifndef ADVENTOFCODE2017_DAY02
#define ADVENTOFCODE2017_DAY02

#include "../includes/aoc.h"

class Day02 {
private:
	std::vector<std::string> inputVec;
	std::vector<std::vector<int32_t>> numbers;
	
	void prepare_data()
	{
		for (auto& line : inputVec)
		{
			auto numbers_single = util::splitInt(line, '\t');
			std::sort(numbers_single.begin(), numbers_single.end());
			numbers.push_back(numbers_single);
		}
	}

	int64_t part1()
	{
		int64_t result = 0;

		for (auto& numberLine : numbers)
		{
			result += numberLine[numberLine.size() - 1] - numberLine[0];
		}

		return result;
	}

	int64_t part2()
	{
		int64_t result = 0;

		for (auto& numberLine : numbers)
		{
			for (int i = 0; i < numberLine.size() - 1; ++i)
			{
				for (int j = i + 1; j < numberLine.size(); ++j)
				{
					if (numberLine[j] % numberLine[i] == 0)
						result += numberLine[j] / numberLine[i];
				}
			}
		}

		return result;
	}

public:
	Day02()
	{
		inputVec = util::readFileLines("..\\inputs\\2017\\input_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		prepare_data();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << std::endl
                  << "Day 02 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2017_DAY02