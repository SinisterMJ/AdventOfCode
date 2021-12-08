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
                if (elem.size() == 2 || elem.size() == 3 || elem.size() == 7 || elem.size() == 4)
                    count++;
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
    
    std::map<std::string, std::string> findMapping(std::vector<std::string> numbers)
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

        for (int ind_b = 0; ind_b < 2; ++ind_b)
        {
            for (int ind_c = 0; ind_c < 2; ++ind_c)
            {
                for (int ind_e = 0; ind_e < 2; ++ind_e)
                {
                    std::map<std::string, std::string> temp_map;
                    temp_map["a"] = entry["a"];
                    temp_map["b"] = entry["b"][ind_b];
                    temp_map["d"] = entry["b"][1 - ind_b];
                    temp_map["c"] = entry["c"][ind_c];
                    temp_map["f"] = entry["c"][1 - ind_c];
                    temp_map["e"] = entry["e"][ind_e];
                    temp_map["g"] = entry["g"][1 - ind_e];

                    bool all_in = true;

                    for (int index = 0; index < 10 && all_in; ++index)
                    {
                        std::string result = "";

                        for (auto ch : numbers[index])
                        {
                            for (auto [cipher, orig] : temp_map)
                            {
                                if (ch == orig[0])
                                    result += cipher;
                            }
                        }

                        std::sort(result.begin(), result.end());

                        if (display_values.count(result) == 0)
                            all_in = false;
                    }

                    if (all_in)
                        return temp_map;
                }
            }
        }

        return entry;
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
                    for (auto [cipher, orig] : entry)
                    {
                        if (ch == orig[0])
                            result += cipher;
                    }
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

        int32_t result_1 = part1();
        int32_t result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY08