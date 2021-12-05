#ifndef ADVENTOFCODE2017_DAY10
#define ADVENTOFCODE2017_DAY10

#include "../includes/aoc.h"
#include <vector>
#include <sstream>

class Day10 {
private:
	std::string input;
    std::vector<int32_t> lengths;
    std::array<uint8_t, 256> hash;

    void swap_positions(int i, int j)
    {        
        i = i % 256;
        j = j % 256;
        std::swap(hash[i], hash[j]);
    }

    int64_t part1()
    {
        int skipSize = 0;
        int position = 0;
        
        for (auto length : lengths)
        {
            for (int i = position, j = position + length - 1; i < j; ++i, --j)
            {
                swap_positions(i, j);
            }

            position += length + skipSize;
            skipSize++;
            position = position % 256;
        }

        return hash[0] * hash[1];
    }

    std::string part2()
    {
        // Reset the hash
        for (int i = 0; i < 256; ++i)
            hash[i] = i;

        int skipSize = 0;
        int position = 0;

        lengths.clear();

        for (auto ch : input)
            lengths.push_back(ch);
        
        lengths.push_back(17);
        lengths.push_back(31);
        lengths.push_back(73);
        lengths.push_back(47);
        lengths.push_back(23);

        for (int index = 0; index < 64; ++index)
        {
            for (auto length : lengths)
            {
                for (int i = position, j = position + length - 1; i < j; ++i, --j)
                {
                    swap_positions(i, j);
                }

                position += length + skipSize;
                skipSize++;
                position = position % 256;
            }
        }

        std::ostringstream result;
        
        for (int offset = 0; offset < 16; ++offset)
        {
            uint8_t number = 0;
            for (int index = 0; index < 16; ++index)
            {
                number = number ^ hash[offset * 16 + index];
            }

            result << std::hex << static_cast<int>(number);
        }

        return result.str();
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

        for (int i = 0; i < 256; ++i)
            hash[i] = i;

        lengths = util::splitInt(input, ',');

        auto result_1 = part1();
        std::string result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout 
            << "Day 10 - Part 1: " << result_1 << '\n'
            << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY10