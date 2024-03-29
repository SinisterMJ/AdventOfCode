#ifndef ADVENTOFCODE2022_DAY03
#define ADVENTOFCODE2022_DAY03

#include "../includes/aoc.h"
#include <set>
#include <algorithm>
#include <iterator>

class Day03 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int64_t sum = 0;
        for (auto line : inputVector)
        {
            std::string first = line.substr(0, line.size() / 2);
            std::string second = line.substr(line.size() / 2);
            int8_t val = 0;
            for (int i = 0; i < first.size() && val == 0; ++i)
            {
                for (int j = 0; j < second.size(); ++j)
                {
                    if (first[i] == second[j])
                    {
                        val = first[i];
                        break;
                    }
                }
            }
            
            if (val >= 'a')
            {
                val -= 'a' - 1;
            }
            else
            {
                val -= 'A' - 1;
                val += 26;
            }

            sum += val;
        }

        return sum;
    }

    int64_t part2()
    {
        int64_t sum = 0;
        for (int index = 0; index < inputVector.size(); index += 3)
        {
            std::set<int8_t> superset;

            for (int i = 0; i < 3; ++i)
            {
                std::set<int8_t> first_set;
                for (auto ch : inputVector[index + i])
                    first_set.insert(ch);

                if (i == 0)
                    superset = first_set;

                std::set<int8_t> intersection;
                std::set_intersection(first_set.begin(), first_set.end(), superset.begin(), superset.end(), std::inserter(intersection, intersection.begin()));
                superset = intersection;
            }

            for (auto val : superset)
            {
                if (val >= 'a')
                {
                    val -= 'a' - 1;
                }
                else
                {
                    val -= 'A' - 1;
                    val += 26;
                }

                sum += val;
            }
        }

        return sum;
    }

public:
    Day03()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_3.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_3.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
                  << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY03