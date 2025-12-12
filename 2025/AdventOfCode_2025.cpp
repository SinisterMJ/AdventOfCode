#include "Day_01.hpp"
#include "Day_02.hpp"
#include "Day_03.hpp"
#include "Day_04.hpp"
#include "Day_05.hpp"
#include "Day_06.hpp"
#include "Day_07.hpp"
#include "Day_08.hpp"
#include "Day_09.hpp"
#include "Day_10.hpp"
#include "Day_11.hpp"
#include "Day_12.hpp"

#include <numeric>
#include <iomanip>
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

	int64_t total_us = 0;

	std::vector<int64_t> runTimes = { };
    
    {
        Day01 mDay01; runTimes.emplace_back(mDay01.run());
        std::cout << std::endl;
    }
    
    {
        Day02 mDay02; runTimes.emplace_back(mDay02.run());
        std::cout << std::endl;
    }

    {
        Day03 mDay03; runTimes.emplace_back(mDay03.run());
        std::cout << std::endl;
    }

    {
        Day04 mDay04; runTimes.emplace_back(mDay04.run());
        std::cout << std::endl;
    }

    {
        Day05 mDay05; runTimes.emplace_back(mDay05.run());
        std::cout << std::endl;
    }

    {
        Day06 mDay06; runTimes.emplace_back(mDay06.run());
        std::cout << std::endl;
    }

    {
        Day07 mDay07; runTimes.emplace_back(mDay07.run());
        std::cout << std::endl;
    }

    {
        Day08 mDay08; runTimes.emplace_back(mDay08.run());
        std::cout << std::endl;
    }

    {
        Day09 mDay09; runTimes.emplace_back(mDay09.run());
        std::cout << std::endl;
    }

    {
        Day10 mDay10; runTimes.emplace_back(mDay10.run());
        std::cout << std::endl;
    }

    {
        Day11 mDay11; runTimes.emplace_back(mDay11.run());
        std::cout << std::endl;
    }

    {
        Day12 mDay12; runTimes.emplace_back(mDay12.run());
        std::cout << std::endl;
    }

	total_us = std::accumulate(runTimes.begin(), runTimes.end(), static_cast<int64_t>(0));

	for (int index = 1; index <= runTimes.size(); ++index)
	{
		std::cout << "Runtime Day " << std::setfill('0') << std::setw(2) << index << ": " << std::setfill(' ') << std::setw(8) << runTimes[index - 1] << "[us]" << std::endl;
	}

	std::cout << std::endl << "Total time needed for all days: " << total_us << "[us]" << std::endl;

	getchar();
	return 0;
}