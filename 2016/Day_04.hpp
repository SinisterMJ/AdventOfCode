#ifndef ADVENTOFCODE2016_DAY04
#define ADVENTOFCODE2016_DAY04

#include "../includes/aoc.h"
#include "../includes/MD5.h"

class Day04 {
private:
	std::string inputString;
public:
	Day04()
	{
		inputString = util::readFile("..\\inputs\\2016\\input_4.txt");
        inputString = inputString.substr(0, inputString.find('\n'));
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        int result_1 = 0;
        int result_2 = 0;

        for (int index = 0;; ++index)
        {
            std::string password = inputString + std::to_string(index);
            std::string hashed = md5(password);

            bool valid = true;
            for (int i = 0; i < 5; ++i)
            {
                if (hashed[i] != '0')
                    valid = false;
            }

            if (valid)
            {
                if (result_1 == 0)
                    result_1 = index;
                
                if (hashed[5] == '0')
                {
                    result_2 = index;
                    break;
                }
            }
        }

		std::cout << "Day 04 - Part 1: " << result_1 << std::endl
				  << "Day 04 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY04