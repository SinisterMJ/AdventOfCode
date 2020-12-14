#ifndef ADVENTOFCODE2020_DAY14
#define ADVENTOFCODE2020_DAY14

#include "../includes/aoc.h"
#include <regex>

class Day14 {
private:
    int64_t orMask;
    int64_t andMask;

    std::map<int64_t, int64_t> memory;

    std::string inputString;
    std::vector<std::string> inputVec;

    void readMask(std::string input)
    {
        std::string mask = input.substr(7);
        andMask = 0xFFFFFFFFFFFFFFFF;
        orMask = 0x0000000000000000;

        for (int index = 0; index < mask.size(); ++index)
        {
            int shift = mask.size() - index - 1;
            if (mask[index] == '0')
                andMask &= ~(int64_t(1) << shift);
            if (mask[index] == '1')
                orMask |= int64_t(1) << shift;
        }
    }

    int64_t getBit(int64_t input, int32_t index)
    {
        return (input >> index) & 1;
    }

    int64_t part2()
    {
        std::regex extract("mem.([0-9]+). = ([0-9]*)");
        std::smatch number_match;

        memory.clear();

        std::string currentMask = "";
        
        for (auto elem : inputVec)
        {
            if (elem.find("mask") != std::string::npos)
                currentMask = elem.substr(7);
            else
            {
                std::regex_search(elem, number_match, extract);
                int64_t address = std::stoll(number_match[1]);
                int64_t value = std::stoll(number_match[2]);

                std::vector<std::string> addresses;
                std::vector<std::string> intermediate;
                
                for (int index = 0; index < currentMask.size(); ++index)
                {
                    if (currentMask[index] != 'X')
                    {
                        if (addresses.size() > 0)
                        {
                            for (auto add : addresses)
                            {
                                if (currentMask[index] == '0')
                                {
                                    intermediate.push_back(add + std::to_string(getBit(address, 35 - index)));
                                }
                                else
                                {
                                    intermediate.push_back(add + "1");
                                }
                            }
                        }
                        else
                        {
                            if (currentMask[index] == '0')
                            {
                                intermediate.push_back(std::to_string(getBit(address, 35)));
                            }
                            else
                            {
                                intermediate.push_back("1");
                            }
                        }
                    }
                    else
                    {
                        if (addresses.size() > 0)
                        {
                            for (auto add : addresses)
                            {
                                intermediate.push_back(add + std::string(1, '0'));
                                intermediate.push_back(add + std::string(1, '1'));
                            }
                        }
                        else
                        {
                            intermediate.push_back(std::string(1, '0'));
                            intermediate.push_back(std::string(1, '1'));
                        }
                    }

                    std::swap(addresses, intermediate);
                    intermediate.clear();
                }

                for (auto add : addresses)
                {
                    int64_t currAdd = std::bitset<64>(add).to_ullong();
                    memory[currAdd] = value;
                }
            }
        }

        int64_t total = 0;
        for (auto elem : memory)
        {
            total += elem.second;
        }

        return total;
    }

    int64_t part1()
    {
        std::regex extract("mem.([0-9]+). = ([0-9]*)");
        std::smatch number_match;

        for (auto elem : inputVec)
        {
            if (elem.find("mask") != std::string::npos)
                readMask(elem);
            else
            {
                std::regex_search(elem, number_match, extract);
                int64_t address = std::stoll(number_match[1]);
                int64_t value = std::stoll(number_match[2]);

                value &= andMask;
                value |= orMask;

                memory[address] = value;
            }
        }
        
        int64_t total = 0;
        for (auto elem : memory)
        {
            total += elem.second;
        }

        return total;
    }

public:
    Day14()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_14.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_14.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY14
