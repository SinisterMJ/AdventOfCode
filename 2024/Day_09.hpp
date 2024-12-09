#ifndef ADVENTOFCODE2024_DAY09
#define ADVENTOFCODE2024_DAY09

#include "../includes/aoc.h"
#include <algorithm>

class Day09 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        std::vector<int32_t> memory;
        int counter = 0;
        
        for (auto ch : inputVector[0])
        {
            int value = counter / 2;
            if (counter % 2 == 1)
                value = -1;

            for (int i = 0; i < (ch - '0'); ++i)
                memory.push_back(value);

            counter++;
        }

        int last = static_cast<int>(memory.size() - 1);
        int first = 0;

        for (;;)
        {
            while (memory[last] == -1)
                last--;

            while (memory[first] != -1)
                first++;

            if (first >= last)
                break;

            std::swap(memory[first], memory[last]);
        }

        int64_t result = 0;

        for (int index = 0; index < memory.size(); ++index)
        {
            if (memory[index] != -1)
                result += index * memory[index];
        }

        return result;
    }

    int64_t part2()
    {
        std::vector<int32_t> memory;
        int counter = 0;

        for (auto ch : inputVector[0])
        {
            int value = counter / 2;
            if (counter % 2 == 1)
                value = -1;

            for (int i = 0; i < (ch - '0'); ++i)
                memory.push_back(value);

            counter++;
        }

        int last = static_cast<int>(memory.size() - 1);
        int first = 0;

        for (;;)
        {
            while (memory[last] == -1)
                last--;

            if (last < 0)
                break;

            int end = last;
            int value = memory[last];
            int count = 0;
            while (last >= 0 && memory[last] == value)
            {
                last--;
                count++;
            }

            first = 0;
            while (true)
            {
                while (memory[first] != -1)
                    ++first;

                int start = first;
                int place = 0;
                while (first < memory.size() && memory[first] == -1)
                {
                    first++;
                    place++;
                }

                if (start < end and place >= count)
                {
                    for (int i = 0; i < count; ++i)
                        std::swap(memory[start + i], memory[end - i]);

                    break;
                }

                if (first >= last)
                    break;
            }
            
            if (last <= 0)
                break;
        }

        int64_t result = 0;

        for (int index = 0; index < memory.size(); ++index)
            if (memory[index] != -1)
                result += index * memory[index];

        return result;
    }

public:
    Day09()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY09