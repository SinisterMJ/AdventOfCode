#ifndef ADVENTOFCODE2022_DAY11
#define ADVENTOFCODE2022_DAY11

#include "../includes/aoc.h"

class Day11 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Monkey
    {
        std::vector<int64_t> items;
        int64_t factor;
        bool multiply;
        bool square;
        int64_t divisible;
        int64_t target_true;
        int64_t target_false;
        int64_t monkey_business;
    };

    std::vector<Monkey> monkeys;

    void read_data()
    {
        Monkey temp;
        temp.monkey_business = 0;
        for (auto line : inputVector)
        {
            if (line == "")
            {
                monkeys.push_back(temp);
                temp.items.clear();
            }

            if (line.find("Starting items: ") != std::string::npos)
            {
                auto list = line.substr(std::string("  Starting items: ").size());
                auto list_split = util::split(list, ", ");
                for (auto item : list_split)
                    temp.items.push_back(std::stoi(item));
            }

            if (line.find("  Operation: new = ") != std::string::npos)
            {
                auto op = line.substr(std::string("  Operation: new = ").size());
                if (op.find("+") != std::string::npos)
                    temp.multiply = false;
                else
                    temp.multiply = true;
                
                if (op.substr(std::string("old * ").size()).find("old") != std::string::npos)
                    temp.square = true;
                else
                    temp.square = false;

                if (!temp.square)
                {
                    auto factor = op.substr(std::string("old * ").size());
                    temp.factor = std::stoi(factor);
                }
            }

            if (line.find("  Test: ") != std::string::npos)
                temp.divisible = std::stoi(line.substr(std::string("  Test: divisible by ").size()));

            if (line.find("    If true: throw to monkey ") != std::string::npos)
                temp.target_true = std::stoi(line.substr(std::string("    If true: throw to monkey ").size()));

            if (line.find("    If false: throw to monkey ") != std::string::npos)
                temp.target_false = std::stoi(line.substr(std::string("    If false: throw to monkey ").size()));
        }

        monkeys.push_back(temp);
    }

    int64_t solve(bool apply_lcm)
    {
        monkeys.clear();
        read_data();

        int32_t rounds = apply_lcm ? 10000 : 20;


        int64_t lcm = 1;
        for (auto monkey : monkeys)
            lcm *= monkey.divisible;

        for (int64_t round = 0; round < rounds; ++round)
        {
            for (auto& monkey : monkeys)
            {
                monkey.monkey_business += static_cast<int64_t>(monkey.items.size());
                for (auto item : monkey.items)
                {
                    int64_t worry_level = 0;
                    if (!monkey.multiply)
                        worry_level = item + monkey.factor;
                    else
                    {
                        if (monkey.square)
                            worry_level = item * item;
                        else
                            worry_level = item * monkey.factor;
                    }

                    if (apply_lcm)
                        worry_level = worry_level % lcm;
                    else
                        worry_level /= 3;

                    if (worry_level % monkey.divisible == 0)
                        monkeys[monkey.target_true].items.push_back(worry_level);
                    else
                        monkeys[monkey.target_false].items.push_back(worry_level);
                }

                monkey.items.clear();                
            }
        }

        std::vector<int64_t> business;

        for (auto monkey : monkeys)
            business.push_back(monkey.monkey_business);

        std::sort(business.rbegin(), business.rend());
        
        return business[0] * business[1];
    }

public:
    Day11()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_11.txt", '\n', false);
        inputString = util::readFile("..\\inputs\\2022\\input_11.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = solve(false);
        auto result_2 = solve(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY11