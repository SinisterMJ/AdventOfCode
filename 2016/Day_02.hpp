#ifndef ADVENTOFCODE2016_DAY02
#define ADVENTOFCODE2016_DAY02

#include "../includes/aoc.h"

class Day02 {
private:
	std::vector<std::string> inputVec;

    std::string part1()
    {
        std::string result = "";
        int numbers[3][3] = { { 1, 2, 3}, { 4, 5, 6}, { 7, 8, 9}};
        v2 pos(1, 1);

        for (auto inst : inputVec)
        {
            for (auto ch : inst)
            {
                switch (ch)
                {
                case 'U': pos.y--; break;
                case 'D': pos.y++; break;
                case 'R': pos.x++; break;
                case 'L': pos.x--; break;
                }

                if (pos.y < 0)
                    pos.y = 0;
                if (pos.y > 2)
                    pos.y = 2;
                if (pos.x < 0)
                    pos.x = 0;
                if (pos.x > 2)
                    pos.x = 2;
            }

            result += std::to_string(numbers[pos.y][pos.x]);
        }
        
        return result;
    }

    std::string part2()
    {
        std::string result = "";
        std::string numbers[5][5] = {
            {"0", "0", "1", "0", "0"},
            {"0", "2", "3", "4", "0"},
            {"5", "6", "7", "8", "9"},
            {"0", "A", "B", "C", "0"},
            {"0", "0", "D", "0", "0"}
        };

        v2 pos(0, 2);

        for (auto inst : inputVec)
        {            
            for (auto ch : inst)
            {
                v2 last_pos = pos;
                switch (ch)
                {
                case 'U': pos.y--; break;
                case 'D': pos.y++; break;
                case 'R': pos.x++; break;
                case 'L': pos.x--; break;
                }

                if (pos.y < 0)
                    pos.y = 0;
                if (pos.y > 4)
                    pos.y = 4;
                if (pos.x < 0)
                    pos.x = 0;
                if (pos.x > 4)
                    pos.x = 4;

                if (numbers[pos.y][pos.x] == "0")
                    pos = last_pos;
            }

            result += numbers[pos.y][pos.x];
        }

        return result;
    }

public:
	Day02()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_2.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << std::endl
                  << "Day 02 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2016_DAY02