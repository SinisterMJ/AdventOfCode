#ifndef ADVENTOFCODE2020_DAY25
#define ADVENTOFCODE2020_DAY25

#include "../includes/aoc.h"

class Day25 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1() 
    {
        int64_t result = 0;

        auto publicKeys = util::ConvertToInt64(inputVec);
        
        result = 1;
        
        int64_t value = 1;
        int64_t subjectNumber = 7;
        int64_t remainder = 20201227;

        int64_t rounds_0 = 0;
        int64_t rounds_1 = 0;

        for ( int round = 0; rounds_0 == 0 || rounds_1 == 0; ++round )
        {
            value = (value * subjectNumber) % remainder;
            if (value == publicKeys[0] && rounds_0 == 0)
                rounds_0 = round + 1;

            if (value == publicKeys[1] && rounds_1 == 0)
                rounds_1 = round + 1;
        }

        for (int round = 0; round < rounds_0; ++round)
        {
            result = (result * publicKeys[1]) % remainder;
        }

        return result;
    }
public:
    Day25()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_25.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_25.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = part1();

        int64_t time = myTime.usPassed();
        std::cout << "Day 25 - Part 1: " << result_1 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY25
