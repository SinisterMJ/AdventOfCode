#ifndef ADVENTOFCODE2022_DAY25
#define ADVENTOFCODE2022_DAY25

#include "../includes/aoc.h"

class Day25 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::string part1()
    {
        int64_t sum = 0;

        for (auto line : inputVector)
        {
            int64_t factor = std::pow(5, line.size() - 1);

            for (auto ch : line)
            {
                if (ch == '2')
                    sum += 2 * factor;
                if (ch == '1')
                    sum += 1 * factor;
                if (ch == '-')
                    sum -= factor;
                if (ch == '=')
                    sum -= 2 * factor;

                factor /= 5;
            }
        }

        int64_t factor = 1;
        while ((factor * 2) < sum)
            factor *= 5;

        std::string result = "";

        for (;;)
        {
            int64_t min_dist = std::numeric_limits<int64_t>::max();
            
            min_dist = std::min(min_dist, std::abs(sum - 2 * factor));
            min_dist = std::min(min_dist, std::abs(sum - 1 * factor));
            min_dist = std::min(min_dist, std::abs(sum));
            min_dist = std::min(min_dist, std::abs(sum + 1 * factor));
            min_dist = std::min(min_dist, std::abs(sum + 2 * factor));

            if (min_dist == std::abs(sum - 2 * factor))
            {
                result += "2";
                sum -= 2 * factor;
            }
            else if (min_dist == std::abs(sum - 1 * factor))
            {
                result += "1";
                sum -= 1 * factor;
            }
            else if (min_dist == std::abs(sum))
            {
                result += "0";
            }
            else if (min_dist == std::abs(sum + 1 * factor))
            {
                result += "-";
                sum += 1 * factor;
            }
            else if (min_dist == std::abs(sum + 2 * factor))
            {
                result += "=";
                sum += 2 * factor;
            }

            factor /= 5;

            if (factor == 0)
            {
                if (result[0] == '0')
                    return result.substr(1);

                return result;
            }
        }
    }

public:
    Day25()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_25.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_25.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();

        int64_t time = myTime.usPassed();

        std::cout << "Day 25 - Part 1: " << result_1 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY25