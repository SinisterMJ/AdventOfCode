#ifndef ADVENTOFCODE2020_DAY06
#define ADVENTOFCODE2020_DAY06

#include "../includes/aoc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

class Day06 {
private:
	std::vector<std::string> inputVec;
    std::string input;

    int32_t ReadReports() 
    {
        int32_t result = 0;
        for (int index = 0; index < inputVec.size(); ++index)
        {
            std::string sEntry = "";            

            while (index < inputVec.size() && inputVec[index] != "")
            {
                sEntry += inputVec[index];
                ++index;
            }

            std::set<char> checker(sEntry.begin(), sEntry.end());
            result += static_cast<int32_t>(checker.size());
        }

        return result;
    }

    int32_t ReadReportsFast()
    {
        int32_t result = 0;

        for (int index = 0; index < inputVec.size(); ++index)
        {
            int32_t combined = 0;

            while (index < inputVec.size() && inputVec[index] != "")
            {
                for (int i = 0; i < inputVec[index].size(); ++i)
                {
                    combined |= 1 << (inputVec[index][i] - 'a');
                }

                ++index;
            }

            result += std::bitset<32>(combined).count();
        }

        return result;
    }

    int32_t ReadReportsCombined() 
    {
        int32_t result = 0;
        for (int index = 0; index < inputVec.size(); ++index)
        {
            std::vector<std::set<char>> checker;
            while (index < inputVec.size() && inputVec[index] != "")
            {
                checker.push_back(std::set<char>(inputVec[index].begin(), inputVec[index].end()));
                ++index;
            }

            std::set<char> intersect = checker[0];
            std::set<char> combined;

            for (int i = 1; i < checker.size(); ++i)
            {
                std::set_intersection(intersect.begin(), intersect.end(), checker[i].begin(), checker[i].end(), std::inserter(combined, combined.begin()));
                std::swap(combined, intersect);
                combined.clear();
            }
            
            result += static_cast<int32_t>(intersect.size());
        }

        return result;
    }

    int32_t ReadReportsCombinedFast()
    {
        int32_t result = 0;
        for (int index = 0; index < inputVec.size(); ++index)
        {
            int32_t combined = 0xFFFFFFFF;
            std::vector<std::set<char>> checker;
            while (index < inputVec.size() && inputVec[index] != "")
            {
                int32_t local = 0;
                for (int i = 0; i < inputVec[index].size(); ++i)
                {
                    local |= 1 << (inputVec[index][i] - 'a');
                }
                combined &= local;
                ++index;
            }

            result += std::bitset<32>(combined).count();
        }

        return result;
    }

public:
	Day06()
	{
		inputVec = util::readFileLines("..\\inputs\\input_2020_6.txt", '\n', false);
        input = util::readFile("..\\inputs\\input_2020_6.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
		
        int32_t result_1 = ReadReportsFast();
        int32_t result_2 = ReadReportsCombinedFast();

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY06
