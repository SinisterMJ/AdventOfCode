#ifndef ADVENTOFCODE2022_DAY13
#define ADVENTOFCODE2022_DAY13

#include "../includes/aoc.h"
#include <algorithm>

class Day13 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<std::string> parse_string(std::string input)
    {
        std::vector<std::string> result;
        int inside_list = 0;
        std::string temp = "";
        for (int index = 0; index < input.size(); ++index)
        {
            if (input[index] == '[')
                inside_list++;

            if (input[index] == ']')
                inside_list--;

            if (input[index] != ',')
                temp += std::string(1, input[index]);

            if (input[index] == ',' && inside_list > 0)
                temp += std::string(1, input[index]);

            if (input[index] == ',' && inside_list == 0)
            {
                result.push_back(temp);
                temp = "";
            }
        }
        result.push_back(temp);

        return result;
    }

    int check_order(std::string left, std::string right)
    {
        bool list_left = false;
        if (left[0] == '[')
        {
            list_left = true;
            left = left.substr(1, left.size() - 2);
        }

        bool list_right = false;
        if (right[0] == '[')
        {
            list_right = true;
            right = right.substr(1, right.size() - 2);
        }

        if (!list_right && !list_left)
        {
            int left_val = -1;
            if (left != "")
                left_val = std::stoi(left);

            int right_val = -1;
            if (right != "")
                right_val = std::stoi(right);

            if (left_val < right_val)
                return 1;
            
            if (left_val == right_val)
                return 0;
            
            if (left_val > right_val)
                return -1;
        }

        if (list_right && list_left)
        {
            std::vector<std::string> left_el = parse_string(left);
            std::vector<std::string> right_el = parse_string(right);

            for (int index = 0; index < right_el.size(); ++index)
            {
                if (left_el.size() == index)
                    return 1;

                int result = check_order(left_el[index], right_el[index]);

                if (result != 0)
                    return result;
            }

            if (left_el.size() > right_el.size())
                return -1;

            return 0;
        }

        if (!list_left || !list_right)
        {
            if (left == "" && list_right)
                return 1;
            if (right == "" && list_left)
                return -1;
            left = "[" + left + "]";
            right = "[" + right + "]";
            return check_order(left, right);
        }

        return -1;
    }

    int part1()
    {
        int sum = 0;
        for (int index = 0; index < inputVector.size(); index += 3)
        {
            if (check_order(inputVector[index], inputVector[index + 1]) == 1)
                sum += index / 3 + 1;
        }

        return sum;
    }

    int part2()
    {
        std::vector<std::string> messages;

        messages.push_back("[[2]]");
        messages.push_back("[[6]]");

        for (auto line : inputVector)
            if (line != "")
                messages.push_back(line);

        std::sort(messages.begin(), messages.end(), 
            [this](const std::string& left, const std::string& right)
            {
                return check_order(left, right) == 1;
            }
        );

        int in_1 = 0;
        int in_2 = 0;

        for (int index = 0; index < messages.size(); ++index)
        {
            if (messages[index] == "[[2]]")
                in_1 = index + 1;
            if (messages[index] == "[[6]]")
                in_2 = index + 1;
        }

        return in_1 * in_2;
    }

public:
    Day13()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_13.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_13.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 13 - Part 1: " << result_1 << '\n'
                  << "Day 13 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY13