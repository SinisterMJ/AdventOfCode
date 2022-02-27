#ifndef ADVENTOFCODE2016_DAY07
#define ADVENTOFCODE2016_DAY07

#include "../includes/aoc.h"
#include <map>
#include <regex>

class Day07 {
private:
    std::vector<std::string> inputVec;

    bool checkABBA(std::string input)
    {
        if (input.size() < 3)
            return false;

        for (int index = 0; index < input.size() - 3; ++index)
        {
            if (input[index + 0] == input[index + 3] &&
                input[index + 1] == input[index + 2] &&
                input[index + 0] != input[index + 1])
                return true;
        }

        return false;
    }

    int64_t part1()
    {
        int result = 0;

        for (auto elem : inputVec)
        {
            //elem = "abba[mnop]qrst";
            std::vector<std::string> outside_brackets;
            std::vector<std::string> inside_brackets;

            while (elem.find('[') != std::string::npos)
            {
                // Find brackets. Can be multiple
                int64_t brack_start = elem.find('[');
                int64_t brack_end = elem.find(']');
                inside_brackets.emplace_back(elem.substr(brack_start + 1, brack_end - brack_start - 1));
                outside_brackets.emplace_back(elem.substr(0, brack_start));
                elem = elem.substr(brack_end + 1);
            }

            outside_brackets.emplace_back(elem);

            bool passable = false;

            for (auto str : outside_brackets)
                passable |= checkABBA(str);

            for (auto str : inside_brackets)
                passable &= !checkABBA(str);

            result += passable;
        }

        return result;
    }

    int64_t part2()
    {
        int result = 0;

        for (auto elem : inputVec)
        {
            //elem = "aba[bab]xyz";
            std::vector<std::string> outside_brackets;
            std::vector<std::string> inside_brackets;

            while (elem.find('[') != std::string::npos)
            {
                // Find brackets. Can be multiple
                int64_t brack_start = elem.find('[');
                int64_t brack_end = elem.find(']');
                inside_brackets.emplace_back(elem.substr(brack_start + 1, brack_end - brack_start - 1));
                outside_brackets.emplace_back(elem.substr(0, brack_start));
                elem = elem.substr(brack_end + 1);
            }

            outside_brackets.emplace_back(elem);

            bool passable = false;

            for (auto outer : outside_brackets)
            {
                for (int index = 0; index < outer.size() - 2; ++index)
                {
                    if (outer[index] == outer[index + 2] && outer[index] != outer[index + 1])
                    {
                        std::string search_string = "";
                        search_string += outer[index + 1];
                        search_string += outer[index + 0];
                        search_string += outer[index + 1];

                        for (auto inner : inside_brackets)
                        {
                            if (inner.find(search_string) != std::string::npos)
                                passable = true;
                        }
                    }
                }
            }

            result += passable;
        }

        return result;
    }

public:
	Day07()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_7.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << std::endl
                  << "Day 07 - Part 2: " << result_2 << std::endl;

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY07