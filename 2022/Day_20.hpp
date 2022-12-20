#ifndef ADVENTOFCODE2022_DAY20
#define ADVENTOFCODE2022_DAY20

#include "../includes/aoc.h"

class Day20 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t solve(int64_t _factor, int64_t loop_count)
    {
        auto numbers_orig = util::ConvertToInt(inputVector);
        std::vector<std::pair<int64_t, int64_t>> numbers;
        numbers.reserve(numbers_orig.size());
        int64_t factor = _factor;

        for (int i = 0; i < numbers_orig.size(); ++i)
            numbers.push_back(std::make_pair(numbers_orig[i] * factor, i));

        for (int loops = 0; loops < loop_count; ++loops)
        {
            for (int index = 0; index < numbers.size(); ++index)
            {
                // Find it
                int64_t index_val = 0;
                for (int i = 0; i < numbers.size(); ++i)
                {
                    if (numbers[i].second == index)
                    {
                        index_val = i;
                        break;
                    }
                }

                int64_t val = numbers[index_val].first;
                numbers.erase(numbers.begin() + index_val);

                int64_t offset = index_val + val;
                int64_t div = (numbers_orig.size() - 1);
                int64_t temp = std::abs(offset / div);
                if (offset < 0)
                {
                    offset += (temp + 1) * (numbers_orig.size() - 1);
                }

                offset %= (numbers_orig.size() - 1);
                numbers.insert(numbers.begin() + offset, std::make_pair(val, index));
            }
        }

        int64_t val_1, val_2, val_3;

        int index_0 = 0;

        for (int index = 0; index < numbers.size(); ++index)
            if (numbers[index].first == 0)
                index_0 = index;

        val_1 = numbers[(index_0 + 1000) % numbers.size()].first;
        val_2 = numbers[(index_0 + 2000) % numbers.size()].first;
        val_3 = numbers[(index_0 + 3000) % numbers.size()].first;

        return val_1 + val_2 + val_3;
    }

public:
    Day20()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_20.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_20.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(1, 1);
        auto result_2 = solve(811589153, 10);

        int64_t time = myTime.usPassed();

        std::cout << "Day 20 - Part 1: " << result_1 << '\n'
                  << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY20