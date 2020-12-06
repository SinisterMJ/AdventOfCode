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

    int32_t ReadReports() {
        int index = 0;
        int32_t result = 0;
        for (; index < inputVec.size(); ++index)
        {
            std::string sEntry = "";            

            while (index < inputVec.size() && inputVec[index] != "")
            {
                sEntry += inputVec[index];
                ++index;
            }

            std::set<char> checker(sEntry.begin(), sEntry.end());
            result += checker.size();
        }

        return result;
    }

    int32_t ReadReportsCombined() {
        int index = 0;
        int32_t result = 0;
        for (; index < inputVec.size(); ++index)
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
            
            result += intersect.size();
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
		
        int32_t result_1 = ReadReports();
        int32_t result_2 = ReadReportsCombined();

        std::cout << "Day 06 - Part 1: " << result_1 << '\n'
                  << "Day 06 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY06
