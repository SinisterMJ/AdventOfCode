#ifndef ADVENTOFCODE2025_DAY08
#define ADVENTOFCODE2025_DAY08

#include "../includes/aoc.h"
#include <algorithm>

class Day08 {
private:

    std::vector<std::string> inputVector;

    std::pair<int64_t, int64_t> run_parts()
    {
        std::vector<v3> boxes;
        int64_t part1_result = 0;

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
            if (index == 1000)
            {
                std::vector<int> counts;
                for (const auto& sets : subsets)
                    counts.push_back(sets.size());

                std::sort(counts.begin(), counts.end(), std::greater<int>());
                part1_result = counts[0] * counts[1] * counts[2];
            }
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

        return std::make_pair(part1_result, boxes[distances[index - 1].second.first].x * boxes[distances[index - 1].second.second].x);
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

        auto result = run_parts();
        auto result_1 = result.first;
        auto result_2 = result.second;

        int64_t time = myTime.usPassed();

        std::cout << "Day 08 - Part 1: " << result_1 << '\n'
                  << "Day 08 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY08