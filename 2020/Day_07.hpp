#ifndef ADVENTOFCODE2020_DAY07
#define ADVENTOFCODE2020_DAY07

#include "../includes/aoc.h"
#include <regex>
#include <map>

class Day07 {
private:
    struct bags {
        std::vector<std::pair<int, std::string>> children;
        int32_t containsShiny;
    };

	std::string inputString;
    std::vector<std::string> inputVec;

    std::map<std::string, bags> allBags;

    void ReadBags() {
        std::regex bag_regex("([0-9]+) (.*) bag");
        std::smatch bag_match;

        for (auto elem : inputVec)
        {
            bags bag;
            bag.containsShiny = -1;

            std::string outer = elem.substr(0, elem.find("bag") - 1);
            std::string inner = elem.substr(elem.find("contain") + 8);
            
            if (inner == "no other bags.")
                continue;
            
            auto innerList = util::split(inner, ',');

            for (auto innerElem : innerList)
            {
                std::regex_search(innerElem, bag_match, bag_regex);
                int count = std::stoi(bag_match[1]);
                std::string color = bag_match[2];

                bag.children.push_back(std::pair<int, std::string>(count, color));
            }

            allBags[outer] = bag;
        }
    }

    bool containsShiny(std::string out)
    {
        if (allBags[out].containsShiny != -1)
            return allBags[out].containsShiny;

        bool result = false;

        for (auto elem : allBags[out].children)
        {
            if (elem.second == "shiny gold")
                return true;
            else
                result |= (containsShiny(elem.second));
        }

        allBags[out].containsShiny = result;
        return result;
    }

    int32_t numberBags()
    {
        int result = 0;

        for (auto elem : allBags)
            result += containsShiny(elem.first);
        
        return result;
    }

    int32_t totalNumberBags(std::string outer) {
        int32_t result = 1;

        for (auto elem : allBags[outer].children)
            result += elem.first * totalNumberBags(elem.second);
        
        return result;
    }

public:
	Day07()
	{
		inputString = util::readFile("..\\inputs\\input_2020_7.txt");
        inputVec = util::readFileLines("..\\inputs\\input_2020_7.txt", '\n', true);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        ReadBags();

        int32_t result_1 = numberBags();
        int32_t result_2 = totalNumberBags("shiny gold") - 1;  // shiny gold doesn't count

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY07
