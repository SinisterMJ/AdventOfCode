#ifndef ADVENTOFCODE2015_DAY24
#define ADVENTOFCODE2015_DAY24

#include "../includes/aoc.h"
#include <set>
#include <bitset>

class Day24 {
private:
	std::vector<std::string> inputVector;
	std::vector<int32_t> input_weights;

	int64_t part(int divisions)
	{
		int32_t sum = 0;
		int64_t min_quantum = std::numeric_limits<int64_t>::max();
		int32_t min_elements = static_cast<int32_t>(input_weights.size());

		for (auto weight : input_weights)
			sum += weight;

		for (int32_t bits = 0; bits < std::pow(2, input_weights.size()); ++bits)
		{
			int32_t local_weight = 0;
			std::bitset<32> bitList(bits);

			if (bitList.count() > min_elements)
				continue;

			for (int8_t i = 0; i < 32; ++i)
				if (bitList[i])
					local_weight += input_weights[i];
			
			if (local_weight == sum / divisions)
			{				
				int64_t quantum = 1;

				for (int8_t i = 0; i < 32; ++i)
					if (bitList[i])
						quantum *= input_weights[i];

				if (quantum < 0)
					quantum = std::numeric_limits<int64_t>::max();

				if (bitList.count() < min_elements)
				{
					min_elements = static_cast<int32_t>(bitList.count());
					min_quantum = quantum;
				}

				min_quantum = std::min(min_quantum, quantum);
			}
		}

		return min_quantum;
	}

public:
	Day24()
	{
		inputVector = util::readFileLines("..\\inputs\\2015\\input_24.txt");
		input_weights = util::ConvertToInt(inputVector);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		int64_t result1 = part(3);
		int64_t result2 = part(4);

		std::cout << "Day 24 - Part 1: " << result1 << std::endl;
		std::cout << "Day 24 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY24