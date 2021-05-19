#ifndef ADVENTOFCODE2017_DAY17
#define ADVENTOFCODE2017_DAY17

#include <map>

#include "../includes/aoc.h"
#include <regex>

class Day17 {
private:
	
    int64_t part1() 
    {
        uint64_t fac_A{ 16807 };
        uint64_t fac_B{ 48271 };
        uint64_t mod_fac{ 2147483647 };

        int64_t count{ 0 };

        uint64_t cur_A = start_A;
        uint64_t cur_B = start_B;

        for (uint64_t i = 0; i < 40'000'000; ++i)
        {
            cur_A *= fac_A;
            cur_A = cur_A % mod_fac;

            cur_B *= fac_B;
            cur_B = cur_B % mod_fac;

            count += ((cur_A & 0xFFFF) == (cur_B & 0xFFFF));
        }

        return count;
    }

    int64_t part2() 
	{
        uint64_t fac_A{ 16807 };
        uint64_t fac_B{ 48271 };
        uint64_t mod_fac{ 2147483647 };

        int64_t count{ 0 };

        uint64_t cur_A = start_A;
        uint64_t cur_B = start_B;

        for (uint64_t i = 0; i < 5'000'000; ++i)
        {
            do {
                cur_A *= fac_A;
                cur_A = cur_A % mod_fac;
            } while (cur_A % 4 != 0);
            do {
                cur_B *= fac_B;
                cur_B = cur_B % mod_fac;
            } while (cur_B % 8 != 0);

            count += ((cur_A & 0xFFFF) == (cur_B & 0xFFFF));
        }

        return count;
    }

    uint64_t start_A{ 873 };
    uint64_t start_B{ 583 };

public:
	Day17()
	{
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
		int64_t result1 = part1();
		int64_t result2 = part2();

		std::cout << "Day 17 - Part 1: " << result1 << std::endl
				  << "Day 17 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY17