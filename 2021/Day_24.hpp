#ifndef ADVENTOFCODE2021_DAY24
#define ADVENTOFCODE2021_DAY24

#include "../includes/aoc.h"

class Day24 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::vector<int32_t> add_x;
    std::vector<int32_t> add_y;
    std::vector<int32_t> div_z;

    std::vector<int8_t> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int64_t> max_z_step;

    int64_t runStep(int8_t length, int64_t z_reg, char w)
    {
        int val = add_x[length] + (z_reg % 26);
        z_reg = z_reg / div_z[length];
        if (val != w)
        {
            z_reg *= 26;
            z_reg += w + add_y[length];
        }

        return z_reg;
    }

    std::vector<std::string> runSearch(int8_t length, int64_t z_reg)
    {
        if (length == 14)
        {
            if (z_reg == 0)
                return std::vector<std::string> { "" };
            return std::vector<std::string>();
        }

        if (z_reg > max_z_step[length])
            return std::vector<std::string>();

        int64_t x_future = add_x[length] + z_reg % 26;

        std::vector<int8_t> list = nums;

        if (1 <= x_future && x_future <= 9)
            list = std::vector<int8_t>{ static_cast<int8_t>(x_future) };

        std::vector<std::string> results;

        for (auto num : list)
        {
            int64_t z_after = runStep(length, z_reg, num);
            auto afterVecs = runSearch(length + 1, z_after);

            for (auto entry : afterVecs)
            {
                results.push_back(std::to_string(num) + entry);
            }
        }

        return results;
    }

    std::pair<int64_t, int64_t> solve()
    {
        int lineNumber = 0;
        for (auto ln : inputVec)
        {
            auto in = util::split(ln, ' ');
            
            if (ln.find("add x ") != std::string::npos && ln.find("add x z") == std::string::npos)
                add_x.push_back(std::stoi(in[2]));
            
            if (ln.find("add y ") != std::string::npos && lineNumber % 18 == 15)
                add_y.push_back(std::stoi(in[2]));

            if (ln.find("div z") != std::string::npos)
                div_z.push_back(std::stoi(in[2]));

            lineNumber++;
        }

        max_z_step.resize(div_z.size());

        for (int index = 0; index < div_z.size(); ++index)
        {
            int num_26 = 0;
            for (int i = index; i < div_z.size(); ++i)
            {
                num_26 += div_z[i] == 26;
            }

            max_z_step[index] = static_cast<int64_t>(std::pow(26, num_26));
        }

        auto results = runSearch(0, 0);

        std::vector<int64_t> i_results;

        for (auto res : results)
            i_results.push_back(std::stoll(res));

        std::sort(i_results.begin(), i_results.end());

        return std::make_pair(i_results[i_results.size() - 1], i_results[0]);
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day24()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_24.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_24.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto res = solve();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 24 - Part 1: " << result_1 << '\n'
            << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
