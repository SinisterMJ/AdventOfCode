#ifndef ADVENTOFCODE2025_DAY08
#define ADVENTOFCODE2025_DAY08

#include "../includes/aoc.h"
#include <algorithm>
#include <numeric>

class Day08 {
private:

    std::vector<std::string> inputVector;

    // Union-Find Datenstruktur
    struct DSU {
        std::vector<int> parent, size;
        
        DSU(int n) : parent(n), size(n, 1)
        {
            std::iota(parent.begin(), parent.end(), 0);
        }
        
        int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
           
            return parent[x];
        }
        
        bool unite(int x, int y)
        {
            int rx = find(x), ry = find(y);
        
            if (rx == ry)
                return false;

            if (size[rx] < size[ry])
                std::swap(rx, ry);
            
            parent[ry] = rx;
            size[rx] += size[ry];
            return true;
        }

        int get_size(int x)
        {
            return size[find(x)];
        }
    };

    std::pair<int64_t, int64_t> run_parts()
    {
        std::vector<v3> boxes;
        std::vector<std::pair<float, std::pair<int, int>>> distances;

        int64_t part1_result = 0;

        for (const std::string& line : inputVector)
        {
            auto coords = util::splitInt64(line, ',');
            boxes.push_back(v3(coords[0], coords[1], coords[2]));
        }

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

        DSU dsu(static_cast<int>(boxes.size()));
        int index = 0;
        int n = static_cast<int>(boxes.size());
        int part1_components = 0;
        while (dsu.get_size(dsu.find(0)) != n)
        {
            if (index == 1000)
            {
                std::vector<int> comp_sizes;
                std::vector<bool> counted(n, false);
                for (int i = 0; i < n; ++i) {
                    int root = dsu.find(i);
                    if (!counted[root]) {
                        comp_sizes.push_back(dsu.get_size(root));
                        counted[root] = true;
                    }
                }
                std::sort(comp_sizes.begin(), comp_sizes.end(), std::greater<int>());
                part1_result = 1;
                for (int i = 0; i < std::min(3, (int)comp_sizes.size()); ++i)
                    part1_result *= comp_sizes[i];
            }
            auto [index_l, index_r] = distances[index].second;
            dsu.unite(index_l, index_r);
            ++index;
        }

        int64_t part2_result = boxes[distances[index - 1].second.first].x * boxes[distances[index - 1].second.second].x;
        return std::make_pair(part1_result, part2_result);
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