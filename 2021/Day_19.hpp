#ifndef ADVENTOFCODE2021_DAY19
#define ADVENTOFCODE2021_DAY19

#include "../includes/aoc.h"
#include <set>

class Day19 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<std::vector<v3>> list_scanners;

    std::map<std::string, v3> find_overlap(std::vector<v3>& first, std::vector<v3>& second)
    {
        std::vector<v3> displacements_first;
        std::vector<v3> displacements_second;

        for (int i = 0; i < first.size(); ++i)
            for (int j = i + 1; j < first.size(); ++j)
                displacements_first.push_back(first[i] - first[j]);

        for (int i = 0; i < second.size(); ++i)
            for (int j = i + 1; j < second.size(); ++j)
                displacements_second.push_back(second[i] - second[j]);

        int count = 0;
        std::map<std::string, v3> mapping;

        for (int i = 0; i < displacements_first.size(); ++i)
        {
            for (int j = 0; j < displacements_second.size(); ++j)
            {
                auto& vec_first = displacements_first[i];
                auto& vec_second = displacements_second[j];

                if (vec_first.length() == vec_second.length())
                {
                    int64_t x = std::abs(vec_first.x);
                    int64_t y = std::abs(vec_first.y);
                    int64_t z = std::abs(vec_first.z);

                    if (x == y || x == z || y == z)
                    {
                        count++;
                        break;
                    }
                    
                    if (std::abs(vec_second.x) == x)
                        mapping["x"] = (vec_second.x == vec_first.x) ? v3(1, 0, 0) : v3(-1, 0, 0);
                    if (std::abs(vec_second.y) == x)
                        mapping["x"] = (vec_second.y == vec_first.x) ? v3(0, 1, 0) : v3(0, -1, 0);
                    if (std::abs(vec_second.z) == x)
                        mapping["x"] = (vec_second.z == vec_first.x) ? v3(0, 0, 1) : v3(0, 0, -1);


                    if (std::abs(vec_second.x) == y)
                        mapping["y"] = (vec_second.x == vec_first.y) ? v3(1, 0, 0) : v3(-1, 0, 0);
                    if (std::abs(vec_second.y) == y)
                        mapping["y"] = (vec_second.y == vec_first.y) ? v3(0, 1, 0) : v3(0, -1, 0);
                    if (std::abs(vec_second.z) == y)
                        mapping["y"] = (vec_second.z == vec_first.y) ? v3(0, 0, 1) : v3(0, 0, -1);


                    if (std::abs(vec_second.x) == z)
                        mapping["z"] = (vec_second.x == vec_first.z) ? v3(1, 0, 0) : v3(-1, 0, 0);
                    if (std::abs(vec_second.y) == z)
                        mapping["z"] = (vec_second.y == vec_first.z) ? v3(0, 1, 0) : v3(0, -1, 0);
                    if (std::abs(vec_second.z) == z)
                        mapping["z"] = (vec_second.z == vec_first.z) ? v3(0, 0, 1) : v3(0, 0, -1);

                    count++;
                    break;
                }
            }
        }

        if (count < 66)
            return std::map<std::string, v3>();
        else
        {
            v3 cross = mapping["x"].cross(mapping["y"]);

            if (cross != mapping["z"])
            {
                mapping["x"] = -mapping["x"];
                mapping["y"] = -mapping["y"];
                mapping["z"] = -mapping["z"];
            }

            return mapping;
        }
    }

    void apply_mapping(std::vector<v3>& second, std::map<std::string, v3> mapping)
    {
        for (auto& vec : second)
        {
            v3 temp = vec;
                        
            vec.x = mapping["x"] * temp;
            vec.y = mapping["y"] * temp;
            vec.z = mapping["z"] * temp;
        }
    }

    void apply_offset(std::vector<v3>& second, v3 offset)
    {
        for (auto& vec : second)
        {
            vec += offset;
        }
    }

    v3 find_offset(std::vector<v3>& first, std::vector<v3>& second)
    {
        std::vector<std::tuple<v3, int, int>> displacements_first;
        std::vector<std::tuple<v3, int, int>> displacements_second;

        for (int i = 0; i < first.size(); ++i)
            for (int j = i + 1; j < first.size(); ++j)
                displacements_first.push_back(std::make_tuple(first[i] - first[j], i, j));
        
        for (int i = 0; i < second.size(); ++i)
            for (int j = i + 1; j < second.size(); ++j)
                displacements_second.push_back(std::make_tuple(second[i] - second[j], i, j));

        v3 offset(0, 0, 0);
        std::vector<v3> offsets;

        for (int i = 0; i < displacements_first.size(); ++i)
        {
            for (int j = 0; j < displacements_second.size(); ++j)
            {
                auto vec_first = std::get<0>(displacements_first[i]);
                auto vec_second = std::get<0>(displacements_second[j]);

                int index_left = std::get<1>(displacements_first[i]);
                int index_second = -1;

                if (vec_first == vec_second)
                    index_second = std::get<1>(displacements_second[j]);
                
                if (vec_first == -vec_second)
                    index_second = std::get<2>(displacements_second[j]);
                
                if (index_second >= 0)
                {
                    // Check if another vector fits as well?
                    int count = 0;
                    for (auto disp : displacements_first)
                    {
                        auto vec = std::get<0>(disp);
                        count += (vec == vec_second) + (vec == -vec_second);
                    }

                    if (count > 1)
                        continue;

                    offset = first[index_left] - second[index_second];
                    offsets.push_back(offset);
                }
            }
        }

        return offset;
    }

    std::pair<int64_t, int64_t> solve()
    {
        std::vector<v3> list;
        for (auto ln : inputVec)
        {
            if (ln.find("scanner") != std::string::npos)
            {
                if (list.size() > 0)
                    list_scanners.push_back(list);

                list.clear();
                continue;
            }

            auto nums = util::splitInt(ln, ',');
            v3 temp(nums[0], nums[1], nums[2]);
            list.push_back(temp);
        }

        list_scanners.push_back(list);

        std::set<int32_t> seen;
        seen.insert(0);
        std::vector<v3> offsets;

        std::map<int32_t, std::vector<int32_t>> overlaps;

        while (seen.size() != list_scanners.size())
        {
            for (int i = 0; i < list_scanners.size(); ++i)
            {
                if (seen.find(i) == seen.end())
                    continue;

                for (int j = 1; j < list_scanners.size(); ++j)
                {   
                    if (seen.find(j) != seen.end() || i == j)
                        continue;

                    auto mapping = find_overlap(list_scanners[i], list_scanners[j]);
                    if (mapping.size() > 0)
                    {
                        apply_mapping(list_scanners[j], mapping);
                        auto offset = find_offset(list_scanners[i], list_scanners[j]);
                        offsets.push_back(offset);
                        apply_offset(list_scanners[j], offset);
                        seen.insert(j);
                    }
                }
            }
        }

        std::set<v3> beacons;

        for (auto& scanner : list_scanners)
            for (auto& beacon : scanner)
                beacons.insert(beacon);
        
        int64_t max_dist = 0;

        for (int i = 0; i < offsets.size(); ++i)
            for (int j = i + 1; j < offsets.size(); ++j)
                max_dist = std::max(max_dist, (offsets[i] - offsets[j]).manhattan());
        
        return std::make_pair(beacons.size(), max_dist);
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day19()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_19.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_19.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto res = solve();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 19 - Part 1: " << result_1 << '\n'
            << "Day 19 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
