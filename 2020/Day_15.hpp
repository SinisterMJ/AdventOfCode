#ifndef ADVENTOFCODE2020_DAY15
#define ADVENTOFCODE2020_DAY15

#include "../includes/aoc.h"

class Day15 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<int64_t> numbers;

    int64_t runGame(int64_t numIterations)
    {
        std::unordered_map<int64_t, int32_t> lastSpoken;
        for (int index = 0; index < numbers.size(); ++index)
        {
            lastSpoken[numbers[index]] = index;
        }

        int64_t last = numbers.back();
        int64_t lastBefore = numbers[numbers.size() - 2];

        for (int index = numbers.size(); index < numIterations; ++index)
        {
            int64_t last = numbers.back();
            lastSpoken[numbers[index - 2]] = index - 2;

            if (lastSpoken.find(last) != lastSpoken.end())
            {
                numbers.push_back(index - 1 - lastSpoken[last]);
            }
            else
            {
                numbers.push_back(0);
            }
        }

        return numbers.back();
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
        numbers = std::vector<int64_t>{ 5, 2,8, 16, 18, 0, 1 };
        int64_t result_1 = runGame(2020);

        numbers = util::splitInt64(inputString, ',');
        numbers = std::vector<int64_t>{ 5, 2,8, 16, 18, 0, 1 };

        int64_t result_2 = runGame(30000000);

        int64_t time = myTime.usPassed();
        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY15
