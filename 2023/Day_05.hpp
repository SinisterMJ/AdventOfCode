#ifndef ADVENTOFCODE2023_DAY05
#define ADVENTOFCODE2023_DAY05

#include "../includes/aoc.h"
#include <algorithm>
#include <queue>

class Day05 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    std::vector<int64_t> seeds;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> seed_soil;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> soil_fertilizer;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> fertilizer_water;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> water_light;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> light_temperature;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> temperature_humidity;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> humidity_location;

    std::vector<std::pair<int64_t, int64_t>> getRanges(std::pair<int64_t, int64_t> input, std::vector<std::tuple<int64_t, int64_t, int64_t>>& remap)
    {
        std::queue<std::pair<int64_t, int64_t>> in;
        std::vector<std::pair<int64_t, int64_t>> out;
        in.push(input);

        while (!in.empty())
        {
            bool found = false;
            auto curr = in.front();
            in.pop();

            for (auto nums : remap)
            {
                if (in_range<int64_t>(curr.first, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums) - 1))
                {
                    found = true;
                    int64_t low = curr.first - std::get<1>(nums) + std::get<0>(nums);
                    int64_t high = 0;

                    if (curr.second > (std::get<1>(nums) + std::get<2>(nums)))
                    {
                        high = std::get<0>(nums) + std::get<2>(nums) - 1;
                        out.push_back(std::make_pair(low, high));
                        in.push(std::make_pair(std::get<1>(nums) + std::get<2>(nums), curr.second));
                    }
                    else
                    {
                        high = curr.second - std::get<1>(nums) + std::get<0>(nums);
                        out.push_back(std::make_pair(low, high));
                    }
                    break;
                }
                else if (in_range<int64_t>(curr.second, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums) - 1))
                {
                    found = true;
                    int64_t low = std::get<0>(nums);
                    int64_t high = curr.second - std::get<1>(nums) + std::get<0>(nums);
                
                    out.push_back(std::make_pair(low, high));
                    in.push(std::make_pair(curr.first, std::get<1>(nums) - 1));
                    break;
                }
            }

            if (!found)
                out.push_back(curr);
        }

        return out;
    }

    int64_t part1()
    {
        auto target = &seed_soil;
        for (auto line : inputVector)
        {
            if (line.find("seeds") != std::string::npos)
            {
                auto seed_l = util::split(line, ':');
                auto seed_nums = util::split(seed_l[1], ' ');

                for (auto entry : seed_nums)
                {
                    seeds.push_back(std::stoll(entry));
                }
            }
            else
            {
                if (line.find("seed-to-soil") != std::string::npos)
                {
                    target = &seed_soil;
                    continue;
                }
                if (line.find("soil-to-fertilizer") != std::string::npos)
                {
                    target = &soil_fertilizer;
                    continue;
                }
                if (line.find("fertilizer-to-water") != std::string::npos)
                {
                    target = &fertilizer_water;
                    continue;
                }
                if (line.find("water-to-light") != std::string::npos)
                {
                    target = &water_light;
                    continue;
                }
                if (line.find("light-to-temperature") != std::string::npos)
                {
                    target = &light_temperature;
                    continue;
                }
                if (line.find("temperature-to-humidity") != std::string::npos)
                {
                    target = &temperature_humidity;
                    continue;
                }
                if (line.find("humidity-to-location") != std::string::npos)
                {
                    target = &humidity_location;
                    continue;
                }
                if (line == "")
                    continue;

                auto nums = util::splitInt64(line, ' ');
                target->push_back(std::make_tuple(nums[0], nums[1], nums[2]));
            }
        }

        int64_t curr_lowest = std::numeric_limits<int64_t>::max();

        for (auto seed : seeds)
        {
            int64_t curr_num = seed;

            for (auto nums : seed_soil)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : soil_fertilizer)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : fertilizer_water)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : water_light)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : light_temperature)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : temperature_humidity)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            for (auto nums : humidity_location)
            {
                if (in_range<int64_t>(curr_num, std::get<1>(nums), std::get<1>(nums) + std::get<2>(nums)))
                {
                    curr_num = curr_num - std::get<1>(nums) + std::get<0>(nums);
                    break;
                }
            }

            curr_lowest = std::min(curr_num, curr_lowest);
        }

        return curr_lowest;
    }

    int64_t part2()
    {
        int64_t curr_lowest = std::numeric_limits<int64_t>::max();

        for (int index = 0; index < seeds.size(); index += 2)
        {
            auto seed_r = std::make_pair(seeds[index], seeds[index] + seeds[index + 1] - 1);
            auto res = getRanges(seed_r, seed_soil);

            auto nextStep = std::vector<std::pair<int64_t, int64_t>>();
            auto temp = std::vector<std::pair<int64_t, int64_t>>();

            for (auto range : res)
            {
                auto res_l = getRanges(range, soil_fertilizer);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto range : nextStep)
            {
                auto res_l = getRanges(range, fertilizer_water);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto range : nextStep)
            {
                auto res_l = getRanges(range, water_light);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto range : nextStep)
            {
                auto res_l = getRanges(range, light_temperature);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto range : nextStep)
            {
                auto res_l = getRanges(range, temperature_humidity);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto range : nextStep)
            {
                auto res_l = getRanges(range, humidity_location);
                for (auto r : res_l)
                    temp.push_back(r);
            }
            std::swap(nextStep, temp);
            temp.resize(0);

            for (auto r : nextStep)
                curr_lowest = std::min(r.first, curr_lowest);
            
        }

        return curr_lowest;
    }

public:
    Day05()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_5.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 05 - Part 1: " << result_1 << '\n'
                  << "Day 05 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY05