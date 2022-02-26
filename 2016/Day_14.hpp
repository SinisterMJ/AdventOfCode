#ifndef ADVENTOFCODE2016_DAY14
#define ADVENTOFCODE2016_DAY14

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

#include <map>
#include <algorithm>


class Day14 {
private:
    struct Reindeer {
        int64_t speed;
        int64_t duration;
        int64_t pause;
        std::string name;
        int64_t points;
        int64_t currentDistance;  
        int64_t interval;
        int64_t distance_one_interval;
    };

    std::vector<Reindeer> reindeers;

    void buildFliers()
    {
        // Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
        std::regex reg("(\\S+) can fly ([0-9]+) km/s for ([0-9]+) second., but then must rest for ([0-9]+) second.");

        std::smatch deer_match;

        for (auto line : input)
        {
            std::regex_search(line, deer_match, reg);

            Reindeer entry;

            entry.name = deer_match[1];
            entry.speed = std::stoi(deer_match[2]);
            entry.duration = std::stoi(deer_match[3]);
            entry.pause = std::stoi(deer_match[4]);
            entry.points = 0;
            entry.currentDistance = 0;
            entry.interval = entry.duration + entry.pause;
            entry.distance_one_interval = entry.duration * entry.speed;

            reindeers.push_back(entry);
        }
    }

    int64_t distanceCovered(const Reindeer& entry, int64_t flytime)
    {
        int64_t distanceCovered = (flytime / entry.interval) * entry.distance_one_interval;
        int64_t remainingSeconds = flytime - (flytime / entry.interval) * entry.interval;

        if (remainingSeconds > entry.duration)
            distanceCovered += entry.duration * entry.speed;
        else
            distanceCovered += remainingSeconds * entry.speed;

        return distanceCovered;
    }

    int64_t part1()
    { 
        int64_t maxDistance = 0;

        for (auto& entry : reindeers)
        {
            maxDistance = std::max(maxDistance, distanceCovered(entry, 2503));
        }

        return maxDistance;
    }

    int64_t part2()
    {
        for (int duration = 1; duration <= 2503; ++duration)
        {
            int64_t maxDistance = 0;
            for (auto& entry : reindeers)
            {
                auto distance = distanceCovered(entry, duration);
                entry.currentDistance = distance;
                maxDistance = std::max(maxDistance, distance);
            }

            for (auto& entry : reindeers)
            {
                if (entry.currentDistance == maxDistance)
                    entry.points++;
            }
        }

        int64_t maxPoints = 0;
        for (const auto& entry : reindeers)
        {
            maxPoints = std::max(maxPoints, entry.points);
        }

        return maxPoints;
    }

	std::vector<std::string> input;
public:
	Day14()
	{
		input = util::readFileLines("..\\inputs\\2016\\input_14.txt");
	}

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        buildFliers();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 14 - Part 1: " << result_1 << '\n'
                  << "Day 14 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY14