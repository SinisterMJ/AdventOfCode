#ifndef ADVENTOFCODE2021_DAY03
#define ADVENTOFCODE2021_DAY03

#include "../includes/aoc.h"

class Day03 {
private:

    std::vector<std::string> inputs;
    std::string input;

    int64_t part1()
    {
        int epsilon = 0;
        int gamma = 0;
        for (int i = 0; i < inputs[0].size(); ++i)
        {
            epsilon = epsilon << 1;
            gamma = gamma << 1;
            int count_1 = 0;

            for (auto& line : inputs)
                if (line[i] == '1')
                    count_1++;

            if (count_1 > inputs.size() / 2)
                gamma = gamma + 1;
            else
                epsilon += 1;
        }

        return epsilon * gamma;
    }

    int64_t part2()
    {
        std::vector<std::string> oxygens;
        std::vector<std::string> co2;
        std::vector<std::string> tempList = inputs;

        for (int i = 0; i < inputs[0].size() && tempList.size() > 1; ++i)
        {
            int count_1 = 0;

            for (auto& line : tempList)
                if (line[i] == '1')
                    count_1++;

            if (count_1 * 2 >= tempList.size())
            {
                for (auto& line : tempList)
                    if (line[i] == '1')
                        oxygens.push_back(line);
            }
            else
            {
                for (auto& line : tempList)
                    if (line[i] == '0')
                        oxygens.push_back(line);
            }

            tempList = oxygens;
            oxygens.clear();
        }

        oxygens = tempList;
        tempList = inputs;

        for (int i = 0; i < inputs[0].size() && tempList.size() > 1; ++i)
        {
            int count_1 = 0;

            for (auto& line : tempList)
                if (line[i] == '1')
                    count_1++;

            if (count_1 * 2 >= tempList.size())
            {
                for (auto& line : tempList)
                    if (line[i] == '0')
                        co2.push_back(line);
            }
            else
            {
                for (auto& line : tempList)
                    if (line[i] == '1')
                        co2.push_back(line);
            }

            tempList = co2;
            co2.clear();
        }

        co2 = tempList;
        int i_co2 = std::stoi(co2[0], nullptr, 2);
        int i_o2 = std::stoi(oxygens[0], nullptr, 2);
        return i_co2 * i_o2;
    }

public:
    Day03()
    {
        inputs = util::readFileLines("..\\inputs\\2021\\input_3.txt");
        input = util::readFile("..\\inputs\\2021\\input_3.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 03 - Part 1: " << result_1 << '\n'
            << "Day 03 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY03