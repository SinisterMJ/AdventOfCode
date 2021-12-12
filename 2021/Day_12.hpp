#ifndef ADVENTOFCODE2021_DAY12
#define ADVENTOFCODE2021_DAY12

#include "../includes/aoc.h"

class Day12 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct Cave {
        std::string name;
        std::vector<std::string> connected;
        bool big_cave;
    };

    std::map<std::string, Cave> all_caves;
    std::set<std::string> paths;

    void build_paths(std::string current_node, std::string curr_path, bool visited_twice)
    {
        auto node = all_caves[current_node];

        if (current_node == "start" || current_node == "end")
        {
            if (curr_path.find(node.name) != std::string::npos)
                return;
        }

        if (!node.big_cave)
        {
            if (curr_path.find(node.name) != std::string::npos && visited_twice)
                return;

            if (curr_path.find(node.name) != std::string::npos)
                visited_twice = true;
        }

        if (node.name == "end")
            paths.insert(curr_path + node.name);

        for (auto ch : node.connected)
        {
            build_paths(ch, curr_path + node.name, visited_twice);
        }
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
            temp_back.name = line[1];
            temp.connected.push_back(line[1]);
            temp_back.connected.push_back(line[0]);

            temp.big_cave = std::isupper(line[0][0]);
            temp_back.big_cave = std::isupper(line[1][0]);

            all_caves[line[0]] = temp;
            all_caves[line[1]] = temp_back;
        }

        all_caves["end"].connected.clear();
    }

    int64_t part1()
    {
        paths.clear();
        build_paths("start", "", true);
        return paths.size();
    }

    int64_t part2()
    {
        paths.clear();
        build_paths("start", "", false);
        return paths.size();
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
