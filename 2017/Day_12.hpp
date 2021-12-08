#ifndef ADVENTOFCODE2017_DAY12
#define ADVENTOFCODE2017_DAY12

#include "../includes/aoc.h"

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct Program {
        int32_t id;
        std::vector<int32_t> connected;
        int32_t groups = 0;
        bool checked{ false };
    };

    std::map<int32_t, Program> all_progs;

    void mark_zero(int index, int group_val)
    {
        auto& el = all_progs[index];
        el.groups = group_val;

        if (el.checked)
            return;

        el.checked = true;

        for (auto& ch : el.connected)
        {
            mark_zero(ch, group_val);
        }
    }

    std::pair<int32_t, int32_t> solve()
    {
        for (auto& line : inputVec)
        {
            Program temp;
            auto pos = line.find(" <-> ");
            auto first = line.substr(0, pos);

            temp.id = std::stoi(first);

            auto second = line.substr(pos + 5);
            second.erase(std::remove(second.begin(), second.end(), ' '), second.end());
            auto list_children = util::split(second, ',');
            
            for (auto& el : list_children)
            {
                temp.connected.push_back(std::stoi(el));
            }

            temp.checked = false;
            temp.groups = (temp.id == 0);
            all_progs[temp.id] = temp;
        }

        for (auto& [index, prog] : all_progs)
        {
            if (!prog.checked)
                mark_zero(index, index);
        }

        int sum = 0;
        std::set<int32_t> allGroups;

        for (auto& [index, prog] : all_progs)
        {
            sum += (prog.groups == 0);
            allGroups.insert(prog.groups);
        }

        return std::make_pair(sum, static_cast<int>(allGroups.size()));
    }

public:
    Day12()
    {
        inputString = util::readFile("..\\inputs\\2017\\input_12.txt");
        inputVec = util::readFileLines("..\\inputs\\2017\\input_12.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result = solve();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 12 - Part 1: " << result_1 << '\n'
            << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2017_DAY10
