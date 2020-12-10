#ifndef ADVENTOFCODE2020_DAY05
#define ADVENTOFCODE2020_DAY05

#include "../includes/aoc.h"
#include <bitset>

class Day05 {
private:
    std::vector<std::string> inputs;
    std::vector<int32_t> seatIds;

    void ReadBoardingpasses()
    {
        for (auto elem : inputs)
        {
            std::replace(elem.begin(), elem.end(), 'F', '0');
            std::replace(elem.begin(), elem.end(), 'B', '1');
            std::replace(elem.begin(), elem.end(), 'L', '0');
            std::replace(elem.begin(), elem.end(), 'R', '1');
            
            seatIds.push_back(std::bitset<32>(elem).to_ulong());
        }
        
        std::sort(seatIds.begin(), seatIds.end());
    }

public:
	Day05()
	{
        inputs = util::readFileLines("..\\inputs\\2020\\input_5.txt", '\n', true);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int32_t result_1 = 0;
        int32_t result_2 = 0;

        ReadBoardingpasses();

        result_1 = seatIds.back();
        for (int index = 1; index < seatIds.size(); ++index)
        {
            if (seatIds[index] - seatIds[index - 1] != 1)
            {
                result_2 = seatIds[index] - 1;
            }
        }

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY05
