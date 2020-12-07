#ifndef ADVENTOFCODE2020_DAY07
#define ADVENTOFCODE2020_DAY07

#include "../includes/aoc.h"
#include <regex>
#include <map>

class Day07 {
private:
    struct bags {
        std::string outer;
        std::vector<std::pair<int, std::string>> inner;
    };

	std::string inputString;
    std::vector<std::string> inputVec;

    std::map<std::string, std::vector<std::pair<int, std::string>>> allBagsMap;

    void ReadBags() {
        for (auto elem : inputVec)
        {
            std::string outer = elem.substr(0, elem.find("contain"));
            bags single;
            single.outer = outer.substr(0, outer.find("bag") - 1);

            std::string inner = elem.substr(elem.find("contain") + 8);

            if (inner == "no other bags.")
            {
                allBagsMap[single.outer] = std::vector<std::pair<int, std::string>>();
                continue;
            }

            auto innerList = util::split(inner, ',');

            for (auto innerElem : innerList)
            {
                std::regex bag_regex("([0-9]+) (.*) bag");
                std::smatch bag_match;
                std::regex_search(innerElem, bag_match, bag_regex);
                int count = std::stoi(bag_match[1]);
                std::string color = bag_match[2];

                single.inner.push_back(std::pair<int, std::string>(count, color));
            }

            allBagsMap[single.outer] = single.inner;
        }
    }

    bool containsShiny(std::string out)
    {
        if (allBagsMap[out].size() == 0)
            return false;

        bool result = false;
        for (auto elem : allBagsMap[out])
        {
            if (elem.second == "shiny gold")
                return true;
            else
                result |= (containsShiny(elem.second));
        }

        return result;
    }

    int32_t numberBags()
    {
        int result = 0;

        for (auto elem : allBagsMap)
        {
            result += containsShiny(elem.first);
        }

        return result;
    }

    int32_t totalNumberBags(std::string outer) {
        int32_t result = 1;

        auto list = allBagsMap[outer];

        for (auto elem : list)
        {
            result += elem.first * totalNumberBags(elem.second);
        }

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

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY07
