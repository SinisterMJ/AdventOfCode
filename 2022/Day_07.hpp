#ifndef ADVENTOFCODE2022_DAY07
#define ADVENTOFCODE2022_DAY07

#include "../includes/aoc.h"
#include <memory>

class Day07 {
private:

    struct Folder
    {
        std::shared_ptr<Folder> parent;
        std::string name;
        std::vector<std::shared_ptr<Folder>> dirs;
        int32_t total_size = 0;
    };

    std::vector<std::string> inputVector;
    std::string inputString;

    std::shared_ptr<Folder> root;

    void parse()
    {
        root = std::make_shared<Folder>();
        root->name = "/";
        auto curr_folder = root;
        for (auto line : inputVector)
        {
            if (line == "$ ls")
                continue;

            if (line.find("$") == std::string::npos)
            {
                if (line.find("dir ") != std::string::npos)
                {
                    std::shared_ptr<Folder> temp = std::make_shared<Folder>();
                    temp->name = line.substr(4);
                    temp->parent = curr_folder;
                    curr_folder->dirs.push_back(temp);
                }

                if (line.find("dir ") == std::string::npos)
                {                    
                    auto split = util::split(line, ' ');
                    auto tempPtr = curr_folder;
                    while (tempPtr != nullptr)
                    {
                        tempPtr->total_size += std::stoi(split[0]);
                        tempPtr = tempPtr->parent;
                    }
                }
                continue;
            }

            if (line.find("$ cd ..") != std::string::npos)
            {
                curr_folder = curr_folder->parent;
            }
            else
            {
                std::string target = line.substr(5);
                for (auto& child : curr_folder->dirs)
                    if (child->name == target)
                        curr_folder = child;
            }
        }
    }

    int64_t total_size(std::shared_ptr<Folder> curr)
    {
        int64_t sum = 0;

        for (auto child : curr->dirs)
            sum += total_size(child);

        if (curr->total_size <= 100000)
            return sum + curr->total_size;

        return sum;
    }

    int64_t part1()
    {
        parse();
        return total_size(root);
    }

    int64_t closest(std::shared_ptr<Folder> curr, int64_t current, int64_t deletable)
    {
        if (curr->total_size < deletable)
            return current;

        if (curr->total_size > deletable && current > curr->total_size)
            current = curr->total_size;

        if (curr->dirs.size() == 0)
            return current;

        for (auto child : curr->dirs)
            current = closest(child, current, deletable);

        return current;
    }

    int64_t part2()
    {
        int64_t deletable = root->total_size - 70000000 + 30000000;
        return closest(root, root->total_size, deletable);
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