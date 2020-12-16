#ifndef ADVENTOFCODE2020_DAY15
#define ADVENTOFCODE2020_DAY15

#include "../includes/aoc.h"
#include <map>

class Day15 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<int64_t> numbers;

    int64_t runGame(int64_t numIterations)
    {
        std::vector<int64_t> lastSpokenVec(numIterations);

        for (int index = 0; index < numbers.size(); ++index)
        {
            lastSpokenVec[numbers[index]] = index + 1;
        }

        int64_t last = numbers.back();
        int64_t lastBefore = numbers[numbers.size() - 2];

        for (int64_t index = numbers.size(); index < numIterations; ++index)
        {
            lastSpokenVec[lastBefore] = index - 1;
            lastBefore = last;

            if (lastSpokenVec[last] != 0)
            {
                last = index - lastSpokenVec[last];
            }
            else
            {
                last = 0;
            }
        }

        return last;
    }

public:
    Day15()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_15.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_15.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        numbers = util::splitInt64(inputString, ',');

        int64_t result_1 = runGame(2020);
        int64_t result_2 = runGame(30'000'000);

        int64_t time = myTime.usPassed();
        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY15
