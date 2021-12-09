#ifndef ADVENTOFCODE2021_DAY08
#define ADVENTOFCODE2021_DAY08

#include "../includes/aoc.h"

class Day08 {
private:

    std::string inputString;
    std::vector<std::string> inputVector;

    std::map<std::string, int32_t> int_display;
    std::set<std::string> display_values;

    int64_t part1()
    {
        int64_t count = 0;
        for (auto line : inputVector)
        {
            auto first_second = util::split(line, '|');
            auto second = util::split(first_second[1], ' ');

            for (auto elem : second)
            {
                count += (elem.size() == 2 || elem.size() == 3 || elem.size() == 7 || elem.size() == 4);
            }
        }
        return count;
    }

    std::string findExtraCharacters(std::string strA, std::string strB)
    {
        std::unordered_map<char, int> m1;

        for (int i = 0; i < strB.length(); i++)
            m1[strB[i]]++;

        for (int i = 0; i < strA.length(); i++)
            m1[strA[i]]++;

        std::string result = "";

        for (auto h1 = m1.begin(); h1 != m1.end(); h1++) 
        {
            if (h1->second == 1)
                result += h1->first;
        }

        return result;
    }

    std::map<char, std::string> findMapping(std::vector<std::string> numbers)
    {
        std::map<std::string, std::string> entry;

        for (auto& elem : numbers)
            std::sort(elem.begin(), elem.end());

        int index_1 = 0;
        int index_4 = 0;
        int index_7 = 0;
        int index_8 = 0;

        for (int index = 0; index < numbers.size(); ++index)
        {
            if (numbers[index].size() == 2)
                index_1 = index;
            if (numbers[index].size() == 3)
                index_7 = index;
            if (numbers[index].size() == 4)
                index_4 = index;
            if (numbers[index].size() == 7)
                index_8 = index;
        }

        entry["c"] = numbers[index_1];
        entry["f"] = numbers[index_1];
        entry["a"] = findExtraCharacters(numbers[index_1], numbers[index_7]);
        entry["b"] = findExtraCharacters(numbers[index_1], numbers[index_4]);
        entry["d"] = findExtraCharacters(numbers[index_1], numbers[index_4]);
        entry["e"] = findExtraCharacters(entry["a"], findExtraCharacters(numbers[index_8], numbers[index_4]));
        entry["g"] = entry["e"];

        for (auto& word : numbers)
        {
            if (word.size() == 6 &&
                ((word.find(entry["c"][0]) == std::string::npos) != (word.find(entry["c"][1]) == std::string::npos))
                )
            {
                // Number 6
                auto cf = entry["c"];
                if (word.find(cf[0]) != std::string::npos)
                {
                    entry["c"] = cf[1];
                    entry["f"] = cf[0];
                }
                else
                {
                    entry["c"] = cf[0];
                    entry["f"] = cf[1];
                }
                break;
            }
        }

        for (auto& word : numbers)
        {
            if (word.size() == 6 &&
                ((word.find(entry["b"][0]) == std::string::npos) != (word.find(entry["b"][1]) == std::string::npos))
                )
            {
                // Number 0
                auto bd = entry["b"];
                if (word.find(bd[0]) != std::string::npos)
                {
                    entry["b"] = bd[0];
                    entry["d"] = bd[1];
                }
                else
                {
                    entry["b"] = bd[1];
                    entry["d"] = bd[0];
                }
                break;
            }
        }

        for (auto& word : numbers)
        {
            if (word.size() == 6 &&
                ((word.find(entry["e"][0]) == std::string::npos) != (word.find(entry["e"][1]) == std::string::npos))
                )
            {
                // Number 9
                auto eg = entry["e"];
                if (word.find(eg[0]) != std::string::npos)
                {
                    entry["e"] = eg[1];
                    entry["g"] = eg[0];
                }
                else
                {
                    entry["e"] = eg[0];
                    entry["g"] = eg[1];
                }
                break;
            }
        }

        std::map<char, std::string> result;

        for (auto [key, value] : entry)
        {
            result[value[0]] = key;
        }

        return result;
    }
    
    int64_t part2()
    {
        int_display["abcefg"] = 0;
        int_display["cf"] = 1;
        int_display["acdeg"] = 2;
        int_display["acdfg"] = 3;
        int_display["bcdf"] = 4;
        int_display["abdfg"] = 5;
        int_display["abdefg"] = 6;
        int_display["acf"] = 7;
        int_display["abcdefg"] = 8;
        int_display["abcdfg"] = 9;
        
        for (auto& el : int_display)
            display_values.insert(el.first);

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
                
                for (auto ch : el)
                {
                    result += entry[ch];
                }

                std::sort(result.begin(), result.end());

                number += int_display[result];
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