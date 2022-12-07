#ifndef ADVENTOFCODE2022_DAY07
#define ADVENTOFCODE2022_DAY07

#include "../includes/aoc.h"
#include <stack>

class Day07 {
private:

    struct folder
    {
        folder* parent;
        std::string name;
        std::vector<folder*> dirs;
        std::vector<std::pair<int, std::string>> files;
        int32_t total_size = 0;
    };

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<folder*> root;

    void parse()
    {
        root.resize(1);
        root[0] = new folder();
        root[0]->name = "/";
        auto curr_folder = root[0];
        for (auto line : inputVector)
        {
            if (line.find("$ ls") != std::string::npos)
                continue;

            if (line.find("$") == std::string::npos)
            {
                if (line.find("dir ") != std::string::npos)
                {
                    folder* temp = new folder();
                    temp->name = line.substr(4);
                    temp->parent = curr_folder;
                    curr_folder->dirs.push_back(temp);
                }

                if (line.find("dir ") == std::string::npos)
                {
                    folder* temp = new folder();
                    auto split = util::split(line, ' ');
                    temp->parent = curr_folder;
                    curr_folder->files.push_back(std::make_pair(std::stoi(split[0]), split[1]));
                    curr_folder->total_size += std::stoi(split[0]);
                }
                continue;
            }

            if (line.find("cd ..") != std::string::npos)
            {
                auto size = curr_folder->total_size;
                curr_folder = curr_folder->parent;
                curr_folder->total_size += size;                
            }
            else
            {
                std::string target = line.substr(5);
                for (auto& child : curr_folder->dirs)
                {
                    if (child->name == target)
                    {
                        curr_folder = child;
                        break;
                    }
                }
            }
        }

        while (curr_folder->parent != nullptr)
        {
            auto size = curr_folder->total_size;
            curr_folder = curr_folder->parent;
            curr_folder->total_size += size;
        }

        int32_t sum = 0;
        for (auto child : root[0]->dirs)
        {
            sum += child->total_size;
        }
        for (auto file : root[0]->files)
        {
            sum += file.first;
        }

        root[0]->total_size = sum;
    }

    int64_t total_size(folder* curr)
    {
        if (curr->dirs.size() == 0)
        {
            return curr->total_size <= 100000 ? curr->total_size : 0;
        }

        int64_t sum = 0;
        for (auto child : curr->dirs)
        {
            sum += total_size(child);
        }

        if (curr->total_size <= 100000)
            return sum + curr->total_size;

        return sum;
    }

    int64_t part1()
    {
        parse();
        return total_size(root[0]);
    }

    int64_t closest(folder* curr, int64_t current, int64_t deletable)
    {
        if (curr->total_size < deletable)
        {
            return current;
        }

        if (curr->total_size > deletable && current > curr->total_size)
        {
            current = curr->total_size;
        }

        if (curr->dirs.size() == 0)
        {
            return current;
        }

        for (auto child : curr->dirs)
        {
            current = closest(child, current, deletable);
        }

        return current;
    }

    int64_t part2()
    {
        int64_t deletable = root[0]->total_size - 70000000 + 30000000;
        return closest(root[0], root[0]->total_size, deletable);
    }

public:
    Day07()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_7.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY07