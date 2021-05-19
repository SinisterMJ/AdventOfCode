#ifndef ADVENTOFCODE2017_DAY10
#define ADVENTOFCODE2017_DAY10

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

class Day10 {
private:
	std::string input;

    int64_t part1()
    {

        for (int index = 0; index < 40; ++index)
        {
            std::string nextStep = "";

            int currCounter = 0;
            char last = ' ';

            for (int i = 0; i < input.size(); ++i, ++currCounter)
            {
                if (input.at(i) != last && last != ' ')
                {
                    nextStep += std::to_string(currCounter) + last;
                    currCounter = 0;
                }

                last = input.at(i);
            }

            nextStep += std::to_string(currCounter) + last;

            std::swap(nextStep, input);
        }

        return static_cast<int64_t>(input.size());
    }

    int64_t part2()
    {
        for (int index = 0; index < 10; ++index)
        {
            std::string nextStep = "";

            int currCounter = 0;
            char last = ' ';

            for (int i = 0; i < input.size(); ++i, ++currCounter)
            {
                if (input.at(i) != last && last != ' ')
                {
                    nextStep += std::to_string(currCounter) + last;
                    currCounter = 0;
                }

                last = input.at(i);
            }

            nextStep += std::to_string(currCounter) + last;

            std::swap(nextStep, input);
        }

        return static_cast<int64_t>(input.size());
    }

public:
	Day10()
	{
		input = util::readFile("..\\inputs\\2017\\input_10.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY10