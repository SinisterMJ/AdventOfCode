#ifndef ADVENTOFCODE2016_DAY05
#define ADVENTOFCODE2016_DAY05

#include "../includes/aoc.h"
#include "../includes/MD5.h"

class Day05 {
private:
	std::string input;

    std::pair<std::string, std::string> part1()
    {
        std::string result_1 = "";
        std::string result_2 = "tttttttt";
                
        for (int index = 0;; index++)
        {

            std::string password = input + std::to_string(index);
            std::string hashed = md5(password);

            if (hashed[0] == '0' && hashed[1] == '0' && hashed[2] == '0' && hashed[3] == '0' && hashed[4] == '0')
            {
                if (result_1.size() < 8)
                    result_1 += hashed[5];

                int pos = hashed[5] - '0';
                
                if (in_range<int>(pos, 0, 7))
                    if (result_2[pos] == 't')
                        result_2[pos] = hashed[6];
            }

            if (result_1.size() == 8 && result_2.find('t') == std::string::npos)
            {
                return std::make_pair(result_1, result_2);
            }
        }
    }

public:
	Day05()
	{
		input = util::readFile("..\\inputs\\2016\\input_5.txt");
	}

	int64_t run()
	{
        util::Timer myTime;
        myTime.start();

        auto res = part1();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << std::endl
                  << "Day 05 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY05