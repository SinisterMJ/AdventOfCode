#ifndef ADVENTOFCODE2020_DAY01
#define ADVENTOFCODE2020_DAY01

#include "../includes/aoc.h"
#include <algorithm>
#include <iostream>

class Day01 {
private:
	
	std::vector<std::string> inputVector;
	std::string inputString;

public:
	Day01()
	{
		inputVector = util::readFileLines("..\\inputs\\input_2020_1.txt");
		inputString = util::readFile("..\\inputs\\input_2020_1.txt");
	}

	int64_t run()
	{
		std::vector<int32_t> numbers = util::ConvertToInt(inputVector);

		util::Timer myTime;
		myTime.start();

		int result_1 = -1;
		int result_2 = -1;

		int32_t remainder_1 = 0;
		int32_t remainder_2 = 0;

        std::sort(numbers.begin(), numbers.end());

		for (uint32_t i = 0; i < numbers.size(); ++i)
		{
			remainder_1 = 2020 - numbers[i];
			
			for (uint32_t j = i + 1; j < numbers.size() && numbers[j] <= remainder_1; ++j)
			{
				remainder_2 = 2020 - numbers[i] - numbers[j];
				
                if (result_2 == -1)
                {
                    for (uint32_t k = j + 1; k < numbers.size() && numbers[k] <= remainder_2; ++k)
                    {
                        if (numbers[k] == remainder_2)
                        {
                            result_2 = numbers[i] * numbers[j] * numbers[k];
                            break;
                        }
                    }
                }

				if (numbers[j] == remainder_1)
					result_1 = numbers[i] * numbers[j];
			}            

            if (result_1 != -1 && result_2 != -1)
                break;
		}

		std::cout << "Day 01 - Part 1: " << result_1 << std::endl
				  << "Day 01 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY01