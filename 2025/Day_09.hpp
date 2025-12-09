#ifndef ADVENTOFCODE2025_DAY09
#define ADVENTOFCODE2025_DAY09

#include "../includes/aoc.h"
#include <algorithm>
#include <queue>
#include <array>

class Day09 {
private:

    std::vector<std::string> inputVector;
    std::vector<v2> corners;

    int64_t part1()
    {
        for (auto& line : inputVector)
        {
            auto coords = util::splitInt64(line, ',');
            corners.emplace_back(coords[0], coords[1]);
        }

        int64_t max_area = 0;

        for (int i = 0; i < corners.size() - 1; i++)
        {
            for (int j = i + 1; j < corners.size(); j++)
            {
                const auto& from = corners[i];
                const auto& to = corners[j];
                int64_t area = (1 + std::abs(from.x - to.x)) * (1 + std::abs(from.y - to.y));
                max_area = std::max(area, max_area);
            }
        }

        return max_area;
    }

    int64_t part2()
    {
        std::set<int64_t> x_set;
        std::set<int64_t> y_set;

        for (auto& corner : corners)
        {
            x_set.insert(corner.x);
            y_set.insert(corner.y);
        }

        std::vector x_sorted(x_set.begin(), x_set.end());
        std::vector y_sorted(y_set.begin(), y_set.end());

        std::unordered_map<int64_t, int64_t> x_map;
        std::unordered_map<int64_t, int64_t> y_map;

        for (uint64_t i = 0; i < x_sorted.size(); i++)
            x_map[x_sorted[i]] = i * 2 + 1;

        for (uint64_t i = 0; i < y_sorted.size(); i++)
            y_map[y_sorted[i]] = i * 2 + 1;

        std::vector<std::vector<int>> arr((x_sorted.size() * 2 + 1), std::vector<int>(y_sorted.size() * 2 + 1, 2));

        for (int i = 0; i < corners.size(); ++i)
        {
            v2 start = corners[i];
            start.x = x_map[start.x];
            start.y = y_map[start.y];
            
            v2 end = corners[(i + 1) % corners.size()];
            end.x = x_map[end.x];
            end.y = y_map[end.y];

            v2 dir = (end - start).getDirection();
            v2 current = start;
            
            while (current != end)
            {
                arr[current.x][current.y] = 1;
                current += dir;
            }
            arr[end.x][end.y] = 1;        
        }

        arr[0][0] = 0;
        std::queue<std::pair<int, int>> q;
        q.push({ 0, 0 });

        std::array<std::pair<int, int>, 4> neighbours = { {
            {1, 0},   // rechts
            {-1, 0},  // links
            {0, 1},   // unten
            {0, -1}   // oben
        } };
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : std::array<std::pair<int, int>, 4>{ {{1,0},{-1,0},{0,1},{0,-1}} })
            {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < arr.size() && ny >= 0 && ny < arr[0].size() && arr[nx][ny] == 2)
                {
                    arr[nx][ny] = 0;
                    q.push({ nx, ny });
                }
            }
        }

        for (int x = 0; x < arr.size(); x++)
            for (int y = 0; y < arr[0].size(); y++)
                if (arr[x][y] == 2)
                    arr[x][y] = 1;

        int64_t max_area = 0;

        for (int i = 0; i < corners.size() - 1; i++)
        {
            for (int j = i + 1; j < corners.size(); j++)
            {
                v2 from = corners[i];
                v2 to = corners[j];
                int64_t area = (1 + std::abs(from.x - to.x)) * (1 + std::abs(from.y - to.y));
                if (area < max_area)
                    continue;

                from.x = x_map[from.x];
                from.y = y_map[from.y];
                to.x = x_map[to.x];
                to.y = y_map[to.y];
                bool valid = true;
                for (int64_t x = std::min(from.x, to.x); x <= std::max(from.x, to.x); x++)
                {
                    for (int64_t y = std::min(from.y, to.y); y <= std::max(from.y, to.y); y++)
                    {
                        if (arr[x][y] == 0)
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }

                if (valid)
                    max_area = std::max(area, max_area);
            }
        }

        return max_area;
    }

public:
    Day09()
    {
        inputVector = util::readFileLines("..\\inputs\\2025\\input_9.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2025_DAY09