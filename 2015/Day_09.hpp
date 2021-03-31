#ifndef ADVENTOFCODE2015_DAY09
#define ADVENTOFCODE2015_DAY09

#include "../includes/aoc.h"
#include <map>
#include <tuple>

class Day09 {
private:
    std::vector<std::string> inputVec;
        
    std::map<std::pair<std::string, std::string>, int64_t> connections;
    std::set<std::string> cities;
    std::vector<std::string> vecCities;
    
    void buildConnections()
    {
        for (auto line : inputVec)
        {
            auto first_idx = line.find(" to ");
            auto second_idx = line.find(" = ");
            auto from = line.substr(0, first_idx);
            auto to = line.substr(first_idx + 4, second_idx - first_idx - 4);
            auto distance = line.substr(second_idx + 3);
            int64_t i_distance = std::stoi(distance);

            std::pair<std::string, std::string> key;

            key = from.compare(to) < 0 ? std::make_pair(from, to) : std::make_pair(to, from);
            connections[key] = i_distance;

            cities.insert(from);
            cities.insert(to);
        }

        for (auto city : cities)
            vecCities.push_back(city);
    }
    
    int64_t part1()
    {
        std::sort(vecCities.begin(), vecCities.end());
        int64_t minDistance = std::numeric_limits<int64_t>::max();

        do
        {
            int64_t currentDistance = 0;

            for (int index = 1; index < vecCities.size(); ++index)
            {
                auto from = vecCities[index - 1];
                auto to = vecCities[index];

                std::pair<std::string, std::string> key;
                key = from.compare(to) < 0 ? std::make_pair(from, to) : std::make_pair(to, from);

                currentDistance += connections[key];
            }

            minDistance = std::min(currentDistance, minDistance);
        }
        while (std::next_permutation(vecCities.begin(), vecCities.end()));

        return minDistance;
    }

    int64_t part2()
    {
        std::sort(vecCities.begin(), vecCities.end());
        int64_t maxDistance = 0;

        do
        {
            int64_t currentDistance = 0;

            for (int index = 1; index < vecCities.size(); ++index)
            {
                auto from = vecCities[index - 1];
                auto to = vecCities[index];

                std::pair<std::string, std::string> key;
                key = from.compare(to) < 0 ? std::make_pair(from, to) : std::make_pair(to, from);

                currentDistance += connections[key];
            }

            maxDistance = std::max(currentDistance, maxDistance);
        } while (std::next_permutation(vecCities.begin(), vecCities.end()));

        return maxDistance;
    }

public:
	Day09()
	{
        inputVec = util::readFileLines("..\\inputs\\2015\\input_9.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        buildConnections();
        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 09 - Part 1: " << result_1 << '\n'
                  << "Day 09 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2015_DAY09