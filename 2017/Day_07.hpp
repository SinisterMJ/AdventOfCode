#ifndef ADVENTOFCODE2017_DAY07
#define ADVENTOFCODE2017_DAY07

#include "../includes/aoc.h"
#include <unordered_map>
#include <regex>

class Day07 {
private:
    struct Disc {
        std::vector<std::string> children;
        std::string base;
        int32_t weight;
        std::string name;
        int32_t sub_weight;

        Disc() { weight = 0; name = ""; base = ""; sub_weight = -1; }
    };

    std::unordered_map<std::string, Disc> allDiscs;
	std::vector<std::string> inputVec;

    void ParseDiscs()
    {        
        for (auto& line : inputVec)
        {
            Disc noname;
            if (line.find(" -> ") != std::string::npos)
            {
                noname.children = util::split(line.substr(line.find(" -> ") + 4), ',');
            }
            
            std::string this_disc = line.substr(0, line.find(" -> "));
            noname.name = this_disc.substr(0, this_disc.find(" "));

            if (noname.name == "vazst")
            {
                int breakHere = 0;
            }
            auto pos1 = this_disc.find("(");
            auto pos2 = this_disc.find(")");
            noname.weight = std::stoi(this_disc.substr(pos1 + 1, pos2 - pos1 - 1));

            if (noname.children.size() == 0)
                noname.sub_weight = noname.weight;

            std::string base = allDiscs[noname.name].base;
            noname.base = base;

            for (auto& child : noname.children)
            {
                child.erase(std::remove(child.begin(), child.end(), ' '), child.end());
                auto temp = allDiscs[child];
                temp.base = noname.name;
                allDiscs[child] = temp;
            }

            allDiscs[noname.name] = noname;
        }

        return;
    }

    int32_t calc_weights(std::string node)
    {
        auto& temp = allDiscs[node];
        
        if (temp.sub_weight > 0)
            return temp.sub_weight;

        int32_t total_weight = temp.weight;

        for (auto child : temp.children)
        {
            total_weight += calc_weights(child);
        }

        temp.sub_weight = total_weight;

        return temp.sub_weight;
    }

    std::string part1()
    {
        for (auto& disc : allDiscs)
        {
            if (disc.second.base == "")
                return disc.second.name;
        }
        return "";
    }

    template<typename T>
    std::vector<T> uniqueElements(const std::vector<T>& v) {
        std::unordered_map<T, int> counts;
        for (const auto& elem : v) ++counts[elem];
        std::vector<T> result;
        for (auto [elem, count] : counts)
            if (count == 1)
                result.push_back(elem);
        return result;
    }

    template<typename T>
    std::vector<T> notUniqueElements(const std::vector<T>& v) {
        std::unordered_map<T, int> counts;
        for (const auto& elem : v) ++counts[elem];
        std::vector<T> result;
        for (auto [elem, count] : counts)
            if (count > 1)
                result.push_back(elem);
        return result;
    }

    int64_t part2(std::string start, int32_t offset)
    {
        auto& disc = allDiscs[start];
        
        std::vector<int32_t> subs;
        for (auto child : disc.children)
        {
            subs.push_back(allDiscs[child].sub_weight);
        }

        auto temp = uniqueElements(subs);
        auto temp_2 = notUniqueElements(subs);

        if (temp.size() <= 1)
            return disc.weight + offset;

        if (temp.size() == 2)
        {
            if (offset > 0)
            {
                
            }
        }

        if (offset == 0)
            offset = temp_2[0] - temp[0];
        for (auto child : disc.children)
        {
            if (allDiscs[child].sub_weight == temp[0])
            {
                return part2(child, offset);
            }
        }

        return 0;
    }

public:
	Day07()
	{
		inputVec = util::readFileLines("..\\inputs\\2017\\input_7.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        ParseDiscs();

        std::string result_1 = part1();
        calc_weights(result_1);

        auto result_2 = part2(result_1, 0);

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << std::endl
                  << "Day 07 - Part 2: " << result_2 << std::endl;

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY07