#ifndef ADVENTOFCODE2021_DAY07
#define ADVENTOFCODE2021_DAY07

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
        std::regex bag_regex("([0-9]+) (\\w+ \\w+) bag");
        std::smatch bag_match;

        for (auto elem : inputVec)
        {
            bags bag;
            bag.containsShiny = -1;

            std::string outer = elem.substr(0, elem.find("bag") - 1);
            std::string inner = elem.substr(elem.find("contain") + 8);
            
            // No need to store in map, default is empty vector anyway
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

    void ReadBagsFast() {
        for (auto elem : inputVec)
        {
            bags bag;
            bag.containsShiny = -1;

            std::string outer = elem.substr(0, elem.find("bag") - 1);
            std::string inner = elem.substr(elem.find("contain") + 8);

            // No need to store in map, default is empty vector anyway
            if (inner == "no other bags.")
                continue;

            while (inner.find(',') != std::string::npos || inner.find('.') != std::string::npos)
            {
                // number of bags
                auto pos_number = inner.find(' ');
                int32_t count = std::stoi(inner.substr(0, pos_number));
                std::string color = inner.substr(pos_number + 1, inner.find("bag") - pos_number - 2);
                bag.children.push_back(std::pair<int, std::string>(count, color));

                if (inner.find(',') != std::string::npos)
                    inner = inner.substr(inner.find(',') + 2);
                else
                    break;
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
		inputString = util::readFile("..\\inputs\\2021\\input_7.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_7.txt", '\n', true);
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        ReadBagsFast();

        int32_t result_1 = numberBags();
        int32_t result_2 = totalNumberBags("shiny gold") - 1;  // shiny gold doesn't count

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2021_DAY07
