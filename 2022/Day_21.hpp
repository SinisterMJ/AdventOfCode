#ifndef ADVENTOFCODE2022_DAY21
#define ADVENTOFCODE2022_DAY21

#include "../includes/aoc.h"

class Day21 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Monkey {
        std::string left = "";
        std::string right = "";
        std::string command = "";
        int64_t value = 0;
        bool value_set = false;
        bool saw_human = false;
    };

    std::map<std::string, Monkey> monkeys;

    int64_t solve_monkey(std::string name)
    {
        if (monkeys[name].value_set)
            return monkeys[name].value;

        int64_t val_left = solve_monkey(monkeys[name].left);
        int64_t val_right = solve_monkey(monkeys[name].right);

        if (monkeys[name].command == "+")
            return val_left + val_right;
        if (monkeys[name].command == "*")
            return val_left * val_right;
        if (monkeys[name].command == "/")
            return val_left / val_right;
        if (monkeys[name].command == "-")
            return val_left - val_right;

        return -1;
    }

    int64_t solve_reverse(std::string name, int64_t target)
    {
        if (name == "humn")
            return target;

        if (monkeys[name].value_set)
            return monkeys[name].value;

        if (monkeys[monkeys[name].left].saw_human)
        {
            int64_t subtarget = solve_monkey(monkeys[name].right);

            if (monkeys[name].command == "+")
                return solve_reverse(monkeys[name].left, target - subtarget);

            if (monkeys[name].command == "-")
                return solve_reverse(monkeys[name].left, target + subtarget);

            if (monkeys[name].command == "*")
                return solve_reverse(monkeys[name].left, target / subtarget);

            if (monkeys[name].command == "/")
                return solve_reverse(monkeys[name].left, target * subtarget);
        }

        if (monkeys[monkeys[name].right].saw_human)
        {
            int64_t subtarget = solve_monkey(monkeys[name].left);

            if (monkeys[name].command == "+")
                return solve_reverse(monkeys[name].right, target - subtarget);

            if (monkeys[name].command == "-")
                return solve_reverse(monkeys[name].right, subtarget - target);

            if (monkeys[name].command == "*")
                return solve_reverse(monkeys[name].right, target / subtarget);

            if (monkeys[name].command == "/")
                return solve_reverse(monkeys[name].right, subtarget / target);
        }


        return -1;
    }

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            std::string name = line.substr(0, 4);
            Monkey thisMonkey;

            auto split = util::split(line.substr(6), ' ');
            if (split.size() == 1)
            {
                thisMonkey.value = std::stoi(split[0]);
                thisMonkey.value_set = true;
            }
            else
            {
                thisMonkey.left = split[0];
                thisMonkey.command = split[1];
                thisMonkey.right = split[2];
            }

            monkeys[name] = thisMonkey;
        }

        return solve_monkey("root");
    }

    int64_t part2()
    {
        monkeys.clear();
        for (auto line : inputVector)
        {
            std::string name = line.substr(0, 4);
            Monkey thisMonkey;

            auto split = util::split(line.substr(6), ' ');
            if (split.size() == 1)
            {
                thisMonkey.value = std::stoi(split[0]);
                thisMonkey.value_set = true;
            }
            else
            {
                thisMonkey.left = split[0];
                thisMonkey.command = split[1];
                thisMonkey.right = split[2];
            }

            monkeys[name] = thisMonkey;
        }

        monkeys["humn"].saw_human = true;
        bool propagated = true;

        while (propagated)
        {
            propagated = false;
            for (auto& [name, ape] : monkeys)
            {
                if (ape.saw_human)
                    continue;

                if (ape.left != "" && monkeys[ape.left].saw_human)
                {
                    ape.saw_human = true;
                    propagated = true;
                }
                if (ape.right != "" && monkeys[ape.right].saw_human)
                {
                    ape.saw_human = monkeys[ape.right].saw_human;
                    propagated = true;
                }
            }
        }

        if (!monkeys[monkeys["root"].left].saw_human)
        {
            int64_t target = solve_monkey(monkeys["root"].left);
            return solve_reverse(monkeys["root"].right, target);
        }
        else if (!monkeys[monkeys["root"].right].saw_human)
        {
            int64_t target = solve_monkey(monkeys["root"].right);
            return solve_reverse(monkeys["root"].left, target);
        }

        return 0;
    }

public:
    Day21()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_21.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_21.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY21