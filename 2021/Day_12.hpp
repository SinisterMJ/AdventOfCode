#ifndef ADVENTOFCODE2021_DAY12
#define ADVENTOFCODE2021_DAY12

#include "../includes/aoc.h"

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct Cave {
        std::string name;
        std::vector<std::pair<std::string, int32_t>> connected;
        bool big_cave;
    };

    std::map<std::string, Cave> all_caves;

    int32_t build_paths(std::string current_node, std::string curr_path, bool visited_twice)
    {
        int sum = 0;
        auto node = all_caves[current_node];

        if (curr_path.find(node.name) != std::string::npos && visited_twice)
            return 0;

        if (curr_path.find(node.name) != std::string::npos)
            visited_twice = true;
        
        if (node.name == "end")
            return 1;
        
        for (auto ch : node.connected)
        {
            sum += ch.second * build_paths(ch.first, curr_path + node.name, visited_twice);
        }

        return sum;
    }

    void build_caves()
    {
        for (auto ln : inputVec)
        {
            auto line = util::split(ln, '-');

            Cave temp;
            Cave temp_back;

            if (all_caves.find(line[0]) != all_caves.end())
            {
                temp = all_caves[line[0]];
            }

            if (all_caves.find(line[1]) != all_caves.end())
            {
                temp_back = all_caves[line[1]];
            }

            temp.name = line[0];
            temp.connected.push_back(std::make_pair(line[1], 1));
            temp.big_cave = std::isupper(line[0][0]);

            temp_back.name = line[1];
            temp_back.connected.push_back(std::make_pair(line[0], 1));
            temp_back.big_cave = std::isupper(line[1][0]);

            all_caves[line[0]] = temp;
            all_caves[line[1]] = temp_back;
        }

        std::map<std::string, Cave> all_caves_no_big_caves;

        for (auto& [key, cave] : all_caves)
        {
            int index = 0;
            for (auto target : cave.connected)
            {
                if (target.first == "start")
                {
                    cave.connected.erase(cave.connected.begin() + index);
                    break;
                }

                ++index;
            }
        }

        all_caves["end"].connected.clear();

        for (auto& [key, cave] : all_caves)
        {
            if (!cave.big_cave)
            {
                auto& entry = all_caves_no_big_caves[key];
                entry.name = key;
                entry.big_cave = false;

                for (auto [target, weight] : cave.connected)
                {
                    if (all_caves[target].big_cave)
                    {
                        auto& temp_entry = all_caves[target];
                        for (auto& [name, inner_weight] : temp_entry.connected)
                        {
                            bool found = false;

                            for (auto& [cave_small, inner_weight_small] : entry.connected)
                            {
                                if (cave_small == target)
                                {
                                    found = true;
                                    ++inner_weight_small;
                                }
                            }

                            if (!found)
                            {
                                entry.connected.push_back(std::make_pair(name, 1));
                            }
                        }
                    }
                    else
                    {
                        bool found = false;

                        for (auto& [name, inner_weight] : entry.connected)
                        {
                            if (name == target)
                            {
                                found = true;
                                ++inner_weight;
                            }
                        }
                        
                        if (!found)
                        {
                            entry.connected.push_back(std::make_pair(target, 1));
                        }
                    }
                }
            }
        }

        std::swap(all_caves, all_caves_no_big_caves);
    }

    int32_t part1()
    {   
        return build_paths("start", "", true);
    }

    int32_t part2()
    {
        return build_paths("start", "", false);
    }

public:
    Day12()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_12.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_12.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        build_caves();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 12 - Part 1: " << result_1 << '\n'
                  << "Day 12 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
