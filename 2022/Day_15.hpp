#ifndef ADVENTOFCODE2022_DAY15
#define ADVENTOFCODE2022_DAY15

#include <regex>
#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day15 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    
    struct SensorPair
    {
        v2 sensor;
        int64_t distance = 0;
    };

    std::vector<SensorPair> sensors;
    std::set<v2> beacons;
    
    bool inSensor(v2 position)
    {
        for (auto [sensor, dist] : sensors)
            if ((position - sensor).manhattan() <= dist)
                return true;

        return false;
    }

    void readData()
    {
        std::regex moon_regex("x=(.*), y=(.*): .* x=(.*), y=(.*)");
        std::smatch moon_match;

        for (auto line : inputVector)
        {
            // Sensor at x=2765643, y=3042538: closest beacon is at x=2474133, y=3521072
            if (std::regex_search(line, moon_match, moon_regex) && moon_match.size() >= 5)
            {
                int s_x = std::stoi(moon_match[1]);
                int s_y = std::stoi(moon_match[2]);
                int b_x = std::stoi(moon_match[3]);
                int b_y = std::stoi(moon_match[4]);

                v2 pos(s_x, s_y);
                v2 pos_b(b_x, b_y);

                SensorPair temp;
                temp.distance = (pos_b - pos).manhattan();
                temp.sensor = pos;
                sensors.push_back(temp);
                beacons.insert(pos_b);
            }
        }
    }

    int64_t part1()
    {
        std::vector<std::pair<int64_t, int64_t>> ranges;

        for (auto [sensor, dist] : sensors)
        {
            auto d = dist - std::abs((sensor.y - 2'000'000));
            if (d >= 0)
            {
                int64_t left = sensor.x - d;
                int64_t right = sensor.x + d;

                ranges.push_back(std::make_pair(left, right));
            }
        }

        std::sort(ranges.begin(), ranges.end());
        bool merged = true;

        while (merged)
        {
            merged = false;
            std::vector<std::pair<int64_t, int64_t>> tempRanges;

            for (int i = 0; i < ranges.size(); i++)
            {
                if (i == ranges.size() - 1)
                {
                    tempRanges.push_back(ranges[i]);;
                    continue;
                }

                if (overlap(ranges[i], ranges[i + 1]))
                {
                    tempRanges.push_back(merge_overlap(ranges[i], ranges[i + 1]));
                    merged = true;
                    i++;
                }
                else
                {
                    tempRanges.push_back(ranges[i]);
                }
            }

            if (tempRanges.size() > 0)
                ranges = tempRanges;
        }

        int64_t sum = 0;

        for (auto [left, right] : ranges)
            sum += right - left + 1;

        // Sensors aren't emtpy space
        for (auto [sensor, dist] : sensors)
            if (sensor.y == 2'000'000)
                sum--;

        // Beacons are neither
        for (auto beacon : beacons)
            if (beacon.y == 2'000'000)
                sum--;

        return sum;
    }

    int64_t part2()
    {
        for (auto [sensor, distance] : sensors)
        {
            int64_t x = sensor.x - distance - 1;
            int64_t y = sensor.y;
            v2 test_pos(x, y);
            v2 dir(1, -1);

            while (test_pos.x != sensor.x)
            {
                if (inSensor(test_pos))
                    test_pos += dir;
                else
                    return static_cast<int64_t>(test_pos.x) * 4000000 + static_cast<int64_t>(test_pos.y);
            }

            dir = v2(1, 1);
            while (test_pos.y != sensor.y)
            {
                if (inSensor(test_pos))
                    test_pos += dir;
                else
                    return static_cast<int64_t>(test_pos.x) * 4000000 + static_cast<int64_t>(test_pos.y);
            }

            dir = v2(-1, 1);
            while (test_pos.x != sensor.x)
            {
                if (inSensor(test_pos))
                    test_pos += dir;
                else
                    return static_cast<int64_t>(test_pos.x) * 4000000 + static_cast<int64_t>(test_pos.y);
            }

            dir = v2(-1, -1);
            while (test_pos.y != sensor.y)
            {
                if (inSensor(test_pos))
                    test_pos += dir;
                else
                    return static_cast<int64_t>(test_pos.x) * 4000000 + static_cast<int64_t>(test_pos.y);
            }
        }

        return 0;
    }

public:
    Day15()
    {
        inputVector = util::readFileLines("..\\inputs\\2022\\input_15.txt");
        inputString = util::readFile("..\\inputs\\2022\\input_15.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        readData();
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 15 - Part 1: " << result_1 << '\n'
                  << "Day 15 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2022_DAY15