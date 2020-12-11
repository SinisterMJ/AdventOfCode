#ifndef ADVENTOFCODE2015_DAY06
#define ADVENTOFCODE2015_DAY06

#include "../includes/aoc.h"
#include <regex>

class Day06 {
private:
	std::vector<std::string> inputVec;
    std::map<v2, bool> lightMap;
    std::map<v2, int32_t> lightMap_2;
public:
	Day06()
	{
		inputVec = util::readFileLines("..\\inputs\\2015\\input_6.txt");
	}

	int64_t run()
	{
        util::Timer myTime;
        myTime.start();

        int64_t result_1 = 0;
        int64_t result_2 = 0;

        std::regex light_regex("(.*) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+)");
        std::smatch light_match;

        for (auto elem : inputVec)
        {
            std::regex_search(elem, light_match, light_regex);
            
            int x_min = std::stoi(light_match[2]);
            int y_min = std::stoi(light_match[3]);
            int x_max = std::stoi(light_match[4]);
            int y_max = std::stoi(light_match[5]);

            int id = -1;
            if (light_match[1] == "turn on")
                id = 1;
            if (light_match[1] == "toggle")
                id = 2;

            for (int y = y_min; y <= y_max; ++y)
            {
                for (int x = x_min; x <= x_max; ++x)
                {
                    auto& val = lightMap[v2(x, y)];
                    auto& val_2 = lightMap_2[v2(x, y)];
                    
                    val_2 += id;

                    if (val_2 < 0)
                        val_2 = 0;

                    if (id == -1)
                        val = false;
                    if (id == 1)
                        val = true;
                    if (id == 2)
                        val ^= 1;
                }
            }
        }

        for (auto elem : lightMap)
        {
            result_1 += elem.second;
        }

        for (auto elem : lightMap_2)
        {
            result_2 += elem.second;
        }

        int64_t time = myTime.usPassed();

        std::cout << "Day 06 - Part 1: " << result_1 << std::endl
                  << "Day 06 - Part 2: " << result_2 << std::endl;

        return time;
	}
};

#endif  // ADVENTOFCODE2015_DAY06