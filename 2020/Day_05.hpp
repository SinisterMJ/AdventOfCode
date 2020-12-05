#ifndef ADVENTOFCODE2020_DAY05
#define ADVENTOFCODE2020_DAY05

#include "../includes/aoc.h"

class Day05 {
private:
    std::vector<std::string> inputs;
    std::vector<int32_t> seatIds;

    void ReadBoardingpasses()
    {
        for (auto elem : inputs)
        {
            int32_t row = 0;
            int32_t seat = 0;

            for (int index = 0; index < 7; ++index)
            {
                if (elem[index] == 'B')
                    row |= 0x1 << (6 - index);
            }

            for (int index = 7; index < 10; ++index)
            {
                if (elem[index] == 'R')
                    seat |= 0x1 << (9 - index);
            }

            int32_t seatId = row * 8 + seat;
            seatIds.push_back(seatId);
        }
        
        std::sort(seatIds.begin(), seatIds.end());
    }

public:
	Day05()
	{
        inputs = util::readFileLines("..\\inputs\\input_2020_5.txt", '\n', true);
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

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY05
