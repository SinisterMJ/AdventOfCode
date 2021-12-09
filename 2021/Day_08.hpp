#ifndef ADVENTOFCODE2021_DAY08
#define ADVENTOFCODE2021_DAY08

#include "../includes/aoc.h"

class Day08 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;
    std::array<int32_t, 10> int_values;

    int64_t part1()
    {
        int64_t count = 0;
        
        for (auto line : inputVector)
        {
            auto first_second = util::split(line, '|');
            auto second = util::split(first_second[1], ' ');

            for (auto elem : second)
                count += (elem.size() == 2 || elem.size() == 3 || elem.size() == 7 || elem.size() == 4);
        }

        return count;
    }

    std::map<std::string, int32_t> findMapping(std::vector<std::string> numbers)
    {
        std::map<std::string, int32_t> entry;
        std::array<int32_t, 7> occurrences;

        for (int i = 0; i < 7; ++i)
            occurrences[i] = 0;

        for (auto& num : numbers)
            for (auto& ch : num)
                occurrences[ch - 'a']++;
        
        for (auto& num : numbers)
        {
            int32_t sum = 0;
            
            for (auto& ch : num)
                sum += occurrences[ch - 'a'];

            for (int i = 0; i < 10; ++i)
            {
                if (int_values[i] == sum)
                    entry[num] = i;
            }
        }

        return entry;
    }
    
    int64_t part2()
    {
        // a: 8, b: 6, c: 8, d: 7, e: 4, f: 9, g: 7
        int_values[0] = 8 + 6 + 8 + 4 + 9 + 7;
        int_values[1] = 8 + 9;
        int_values[2] = 8 + 8 + 7 + 4 + 7;
        int_values[3] = 8 + 8 + 7 + 9 + 7;
        int_values[4] = 6 + 8 + 7 + 9;
        int_values[5] = 8 + 6 + 7 + 9 + 7;
        int_values[6] = 8 + 6 + 7 + 4 + 9 + 7;
        int_values[7] = 8 + 8 + 9;
        int_values[8] = 8 + 6 + 8 + 7 + 4 + 9 + 7;
        int_values[9] = 8 + 6 + 8 + 7 + 9 + 7;

        int64_t sum = 0;

        for (auto line : inputVector)
        {
            auto first_second = util::split(line, '|');

            auto first = util::split(first_second[0], ' ');
            auto second = util::split(first_second[1], ' ');

            for (auto& elem : first)
                std::sort(elem.begin(), elem.end());

            auto entry = findMapping(first);

            int number = 0;
            for (auto& el : second)
            {
                number *= 10;
                std::string result = "";

                std::sort(el.begin(), el.end());
                number += entry[el];
            }

            sum += number;
        }

        return sum;
    }

public:
    Day08()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_8.txt");
        inputVector = util::readFileLines("..\\inputs\\2021\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY08