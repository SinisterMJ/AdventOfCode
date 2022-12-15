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
        int distance = 0;
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

    int part1()
    {
        int32_t min_x = std::numeric_limits<int32_t>::max();
        int32_t max_x = std::numeric_limits<int32_t>::min();

        for (auto [sensor, dist] : sensors)
        {
            auto d = dist - (sensor.y - 2'000'000);
            if (d >= 0)
            {
                min_x = std::min(min_x, sensor.x - d);
                max_x = std::max(max_x, sensor.x + d);
            }
        }

        int sum = 0;
        v2 position(0, 2'000'000);
        for (int x = min_x; x <= max_x; ++x)
        {
            position.x = x;
            if (inSensor(position))
                sum++;
        }

        for (auto [sensor, dist] : sensors)
            if (sensor.y == 2'000'000)
                sum--;

        for (auto beacon : beacons)
            if (beacon.y == 2'000'000)
                sum--;

        return sum;
    }

    int64_t part2()
    {
        for (auto [sensor, distance] : sensors)
        {
            int x = sensor.x - distance - 1;
            int y = sensor.y;
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