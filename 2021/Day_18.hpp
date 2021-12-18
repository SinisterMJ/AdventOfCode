#ifndef ADVENTOFCODE2021_DAY18
#define ADVENTOFCODE2021_DAY18

#include "../includes/aoc.h"

class Day18 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    struct Snailnumber {
        Snailnumber* left { nullptr };
        Snailnumber* right { nullptr };
        int32_t val_left = -1;
        int32_t val_right = -1;
        Snailnumber* parent;
        bool passed_comma{ false };

        ~Snailnumber()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

    Snailnumber* parse_line(std::string input)
    {
        Snailnumber* result = new Snailnumber();
        Snailnumber* current = result;

        for (int index = 1; index < input.size() - 1; ++index)
        {
            auto ch = input[index];
            if (ch == '[')
            {
                Snailnumber* temp = new Snailnumber();

                if (current->passed_comma)
                    current->right = temp;
                else
                    current->left = temp;

                temp->parent = current;
                current = temp;
            }

            if (ch == ',')
                current->passed_comma = true;

            if (ch == ']')
            {
                current = current->parent;
            }

            if (ch >= '0' && ch <= '9')
            {
                if (!current->passed_comma)
                    current->val_left = ch - '0';
                else
                    current->val_right = ch - '0';
            }
        }

        return result;
    }

    bool split(Snailnumber* input)
    {
        bool res = false;

        if (input->left != nullptr)
            res |= split(input->left);

        if (res)
            return true;

        if (input->val_left >= 10)
        {
            Snailnumber* newNode = new Snailnumber();
            newNode->parent = input;
            input->left = newNode;
            newNode->val_left = input->val_left / 2;
            newNode->val_right = (input->val_left + 1) / 2;
            input->val_left = -1;

            return true;
        }

        if (input->val_right >= 10)
        {
            Snailnumber* newNode = new Snailnumber();
            newNode->parent = input;
            input->right = newNode;
            newNode->val_left = input->val_right / 2;
            newNode->val_right = (input->val_right + 1) / 2;
            input->val_right = -1;

            return true;
        }

        if (input->right != nullptr && !res)
            res |= split(input->right);

        return res;
    }

    void add_to_right(int32_t val, Snailnumber* input, Snailnumber* current)
    {
        while (current->right == input && current->parent != nullptr)
        {
            input = current;
            current = current->parent;
        }

        if (input != current->right)
        {
            if (current->right == nullptr)
            {
                current->val_right += val;
                return;
            }

            input = current->right;
            while (input->left != nullptr)
                input = input->left;

            input->val_left += val;
        }
    }
     
    void add_to_left(int32_t val, Snailnumber* input, Snailnumber* current)
    {
        while (current->left == input && current->parent != nullptr)
        {
            input = current;
            current = current->parent;
        }

        if (input != current->left)
        {
            if (current->left == nullptr)
            {
                current->val_left += val;
                return;
            }
            input = current->left;
            while (input->right != nullptr)
                input = input->right;

            input->val_right += val;
        }
    }

    bool explode(Snailnumber* input, int depth)
    {
        if (depth < 4)
        {
            if (input->val_left != -1 && input->val_right != -1)
                return false;
        }

        if (depth >= 4)
        {
            int val = input->val_left;
            add_to_left(val, input, input->parent);

            val = input->val_right;
            add_to_right(val, input, input->parent);

            // Delete this node.
            auto parent = input->parent;
            
            if (parent->left == input)
            {
                delete parent->left;
                parent->left = nullptr;
                parent->val_left = 0;
            }

            if (parent->right == input)
            {
                delete parent->right;
                parent->right = nullptr;
                parent->val_right = 0;
            }

            return true;
        }

        bool returnValue = false;

        if (input->left != nullptr)
            returnValue |= explode(input->left, depth + 1);
        if (input->right != nullptr && !returnValue)  // only one explode per iteration
            returnValue |= explode(input->right, depth + 1);

        return returnValue;
    }

    Snailnumber* merge_numbers(Snailnumber* left, Snailnumber* right)
    {
        Snailnumber* result = new Snailnumber();
        result->left = left;
        result->right = right;
        left->parent = result;
        right->parent = result;

        while (true)
        {
            bool changed = explode(result, 0);
            if (!changed)
                changed = split(result);
            if (!changed)
                break;
        }

        return result;
    }

    int32_t get_value(Snailnumber* input)
    {
        int32_t sum = 0;

        if (input->left != nullptr)
            sum += 3 * get_value(input->left);
        else
            sum += 3 * input->val_left;

        if (input->right != nullptr)
            sum += 2 * get_value(input->right);
        else
            sum += 2 * input->val_right;

        return sum;
    }

    std::string get_string(Snailnumber* input)
    {
        std::string result = "[";
        
        if (input->left != nullptr)
            result += get_string(input->left);
        else
            result += std::to_string(input->val_left);

        result += ",";

        if (input->right != nullptr)
            result += get_string(input->right);
        else
            result += std::to_string(input->val_right);

        result += "]";

        return result;
    }

    int32_t part1()
    {
        Snailnumber* result = parse_line(inputVec[0]);
        for (int index = 1; index < inputVec.size(); ++index)
        {
            auto ln = inputVec[index];
            auto thisNumber = parse_line(ln);
            result = merge_numbers(result, thisNumber);
        }

        int32_t result_int = get_value(result);
        delete result;

        return result_int;
    }

    int32_t part2()
    {
        int32_t max = 0;
        for (int i = 0; i < inputVec.size(); ++i)
        {
            for (int j = 0; j < inputVec.size(); ++j)
            {
                if (i == j)
                    continue;

                Snailnumber* first = parse_line(inputVec[i]);
                Snailnumber* second = parse_line(inputVec[j]);

                auto result = merge_numbers(first, second);
                max = std::max(max, get_value(result));

                delete result;
            }
        }

        return max;
    }

public:
    Day18()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_18.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_18.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 18 - Part 1: " << result_1 << '\n'
            << "Day 18 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
