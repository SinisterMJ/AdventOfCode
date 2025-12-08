#ifndef ADVENTOFCODE2025_DAY08
#define ADVENTOFCODE2025_DAY08

#include "../includes/aoc.h"
#include <algorithm>

class Day08 {
private:

    std::vector<std::string> inputVector;

    int64_t part1()
    {
        std::vector<v3> boxes;

        for (const std::string& line : inputVector)
        {
            auto coords = util::splitInt64(line, ',');
            boxes.push_back(v3(coords[0], coords[1], coords[2]));
        }

        std::map<std::pair<int, int>, float> distances;
        std::map<int, int> circuit_map;
        std::vector<float> dist_vec;
        int curr_circuit = 0;

        for (int i = 0; i < boxes.size(); ++i)
        {
            circuit_map[i] = i;
            for (int j = i + 1; j < boxes.size(); ++j)
            {
                v3 diff = boxes[i] - boxes[j];
                float manh = diff.length();

                distances[{i, j}] = manh;
                dist_vec.push_back(manh);
            }
        }

        std::sort(dist_vec.begin(), dist_vec.end());
        std::vector<std::set<int>> set_circuits;

        for (auto& junc_pair : distances)
            for (int i = 0; i < 1000; ++i)
                if (dist_vec[i] == junc_pair.second)
                    set_circuits.push_back({ junc_pair.first.first, junc_pair.first.second });

        bool merged = true;
        while (merged)
        {
            merged = false;
            for (int i = 0; i < set_circuits.size(); ++i)
            {
                for (int j = i + 1; j < set_circuits.size(); ++j)
                {
                    std::set<int> intersection;
                    std::set_intersection(set_circuits[i].begin(), set_circuits[i].end(),
                                          set_circuits[j].begin(), set_circuits[j].end(),
                                          std::inserter(intersection, intersection.begin()));
                    if (!intersection.empty())
                    {
                        set_circuits[i].insert(set_circuits[j].begin(), set_circuits[j].end());
                        set_circuits.erase(set_circuits.begin() + j);
                        merged = true;
                        break;
                    }
                }
                if (merged)
                    break;
            }
        }

        std::vector<int> counts;
        for (const auto& sets : set_circuits)
            counts.push_back(sets.size());

        std::sort(counts.begin(), counts.end(), std::greater<int>());       

        return counts[0] * counts[1] * counts[2];
    }

    int64_t part2()
    {
        std::vector<v3> boxes;

        for (const std::string& line : inputVector)
        {
            auto coords = util::splitInt64(line, ',');
            boxes.push_back(v3(coords[0], coords[1], coords[2]));
        }

        std::vector<std::pair<float, std::pair<int, int>>> distances;
        std::vector<std::set<int>> subsets;
        subsets.push_back(std::set<int>({ 0 }));
        
        for (int i = 0; i < boxes.size(); ++i)
        {            
            for (int j = i + 1; j < boxes.size(); ++j)
            {
                v3 diff = boxes[i] - boxes[j];
                float manh = diff.length();
                distances.push_back({ manh, {i, j} });
            }
        }

        std::sort(distances.begin(), distances.end());

        int index = 0;
        while (subsets[0].size() != boxes.size())
        {
            auto index_l = distances[index].second.first;
            auto index_r = distances[index].second.second;

            bool found = false;
            
            for (auto& s : subsets)
            {
                if (s.contains(index_l) || s.contains(index_r))
                {
                    found = true;
                    s.insert(index_l);
                    s.insert(index_r);
                }
            }

            if (!found)
            {
                auto temp = std::set({ index_l, index_r });
                subsets.push_back(temp);
                ++index;
                continue;
            }

            for (int i = 0; i < subsets.size(); ++i)
            {
                for (int j = i + 1; j < subsets.size(); ++j)
                {
                    std::set<int> intersection;
                    std::set_intersection(subsets[i].begin(), subsets[i].end(),
                        subsets[j].begin(), subsets[j].end(),
                        std::inserter(intersection, intersection.begin()));
                    if (!intersection.empty())
                    {
                        subsets[i].insert(subsets[j].begin(), subsets[j].end());
                        subsets.erase(subsets.begin() + j);
                    }
                }
            }
            ++index;
        }

        return boxes[distances[index - 1].second.first].x * boxes[distances[index - 1].second.second].x;
    }

public:
    Day08()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_8.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY08