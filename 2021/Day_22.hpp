#ifndef ADVENTOFCODE2021_DAY22
#define ADVENTOFCODE2021_DAY22

#include "../includes/aoc.h"

class Day22 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct Area
    {
        bool turnOn{ false };
        int32_t min_z{ 0 };
        int32_t min_y{ 0 };
        int32_t min_x{ 0 };
        int32_t max_z{ 0 };
        int32_t max_y{ 0 };
        int32_t max_x{ 0 };

        int64_t findOverlap(Area a)
        {
            int32_t loc_min_z = std::max(min_z, a.min_z);
            int32_t loc_min_y = std::max(min_y, a.min_y);
            int32_t loc_min_x = std::max(min_x, a.min_x);

            int32_t loc_max_z = std::min(max_z, a.max_z);
            int32_t loc_max_y = std::min(max_y, a.max_y);
            int32_t loc_max_x = std::min(max_x, a.max_x);

            int64_t result = 1;

            if (loc_min_z > loc_max_z || loc_min_y > loc_max_y || loc_min_x > loc_max_x)
                return 0;

            result *= (loc_max_z - loc_min_z + 1);
            result *= (loc_max_y - loc_min_y + 1);
            result *= (loc_max_x - loc_min_x + 1);

            return result;
        }

        Area findOverlapArea(Area a)
        {
            Area temp;

            temp.min_z = std::max(min_z, a.min_z);
            temp.min_y = std::max(min_y, a.min_y);
            temp.min_x = std::max(min_x, a.min_x);
            
            temp.max_z = std::min(max_z, a.max_z);
            temp.max_y = std::min(max_y, a.max_y);
            temp.max_x = std::min(max_x, a.max_x);
                        
            return temp;
        }

        int64_t size()
        {
            int64_t result = 1;
            result *= (max_z - min_z + 1);
            result *= (max_y - min_y + 1);
            result *= (max_x - min_x + 1);

            return result;
        }
    };

    std::vector<Area> proc;

    int64_t solve(bool allLines)
    {
        for (auto ln : inputVec)
        {
            auto task = util::split(ln, ' ');
            auto inst = util::split(task[1], ',');

            Area temp;

            temp.turnOn = (task[0] == "on");

            temp.min_x = std::stoi(inst[0].substr(2, inst[0].find("..") - 2));
            temp.max_x = std::stoi(inst[0].substr(inst[0].find("..") + 2));

            temp.min_y = std::stoi(inst[1].substr(2, inst[1].find("..") - 2));
            temp.max_y = std::stoi(inst[1].substr(inst[1].find("..") + 2));

            temp.min_z = std::stoi(inst[2].substr(2, inst[2].find("..") - 2));
            temp.max_z = std::stoi(inst[2].substr(inst[2].find("..") + 2));
            if (!allLines)
            {
                if (temp.max_z < -50 || temp.max_y < -50 || temp.max_x < -50)
                    continue;

                if (temp.min_z > 50 || temp.min_y > 50 || temp.min_x > 50)
                    continue;
            }

            proc.emplace_back(temp);
        }

        int64_t sum = 0;

        for (int i = 0; i < proc.size(); ++i)
        {
            // Defer responsible of overlap to down the list, thus we don't care about turning off
            if (!proc[i].turnOn)
                continue;

            sum += getArea(proc[i], std::vector<Area>(proc.begin() + i + 1, proc.end()));
        }

        proc.clear();

        return sum;
    }

    int64_t getArea(Area input, std::vector<Area> others)
    {
        int64_t result = input.size();

        std::vector<Area> conflicts;

        for (auto ar : others)
            if (input.findOverlap(ar) > 0)
                conflicts.push_back(input.findOverlapArea(ar));
        
        for (int index = 0; index < conflicts.size(); ++index)
        {
            std::vector<Area> newVec(conflicts.begin() + index + 1, conflicts.end());
            result -= getArea(conflicts[index], newVec);
        }

        return result;
    }

public:
    Day22()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_22.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_22.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 22 - Part 1: " << result_1 << '\n'
            << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
