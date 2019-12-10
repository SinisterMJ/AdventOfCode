#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

const double PI = 3.14159265359;

struct LocDistAngle {
    int32_t x;
    int32_t y;
    float angle;
    double distance;

    LocDistAngle(int32_t d_x, int32_t d_y, int32_t _x, int32_t _y) 
    {
        distance = std::sqrt(d_x * d_x + d_y * d_y);
        if (d_x == 0)
            int breakHere = 0;
        angle = static_cast<float>(std::atan2(d_x, -d_y) / PI * 180.0);
        
        if (angle < 0)
            angle += 360.0;

        x = _x;
        y = _y;
    }

    bool operator<(const LocDistAngle& b) const 
    {
        if (angle != b.angle)
            return angle < b.angle;
        return distance < b.distance;
    }
};

int main()
{
    util::Timer myTime;
    myTime.start();
    
    auto input = util::readFileLines("..\\inputs\\input_2019_10.txt");

    Map2DBase<char> asteroids(static_cast<int32_t>(input.size()), static_cast<int32_t>(input[0].length()), '.');

    for (int y = 0; y < input.size(); ++y)
        for (int x = 0; x < input[y].length(); ++x)
            asteroids.write(x, y, input[y][x]);
    
    int32_t maxAsteroids = 0;
    int32_t laserX, laserY;
    for (int32_t y = 0; y < asteroids.height(); ++y)
    {
        for (int32_t x = 0; x < asteroids.width(); ++x)
        {
            if (asteroids.read(x, y) == '#')
            {
                std::set<float> uniqueAngles;
                for (int32_t search_y = 0; search_y < asteroids.height(); ++search_y)
                {
                    for (int32_t search_x = 0; search_x < asteroids.width(); ++search_x)
                    {
                        if (search_x == x && search_y == y)
                            continue;

                        if (asteroids.read(search_x, search_y) == '#')
                        {
                            LocDistAngle temp(search_x - x, search_y - y, search_x, search_y);
                            uniqueAngles.insert(temp.angle);
                        }
                    }
                }
                if (maxAsteroids < uniqueAngles.size())
                {
                    laserX = x;
                    laserY = y;
                }
                maxAsteroids = std::max<int32_t>(uniqueAngles.size(), maxAsteroids);
            }
        }
    }

    std::vector<LocDistAngle> laserShots;

    for (int x = 0; x < asteroids.width(); ++x)
    {
        for (int y = 0; y < asteroids.height(); ++y)
        {
            if (x == laserX && y == laserY)
                continue;

            if (asteroids.read(x, y) == '#')
                laserShots.push_back(LocDistAngle(x - laserX, y - laserY, x, y));
        }
    }
    
    std::cout << "Result Day 10 Part 1: " << maxAsteroids << std::endl;
    std::sort(laserShots.begin(), laserShots.end());
    
    float lastAngle = -1.f;
    int currentIndex = 0;
    int lastIndex = -1;
    for (int count = 1; laserShots.size() > 0; ++count)
    {
        while (currentIndex == laserShots.size() || lastAngle == laserShots[currentIndex].angle)
        {
            currentIndex++;
            if (currentIndex >= laserShots.size())
                currentIndex = 0;

            // Wrapped around, only points with same angle remain. Choose shortest distance (first element)
            if (lastIndex == currentIndex)
            {
                currentIndex = 0;
                break;
            }
        }

        if (count == 200)
        {
            std::cout << "Result Day 10 Part 2: " << laserShots[currentIndex].x * 100 + laserShots[currentIndex].y << std::endl;
        }

        lastIndex = currentIndex;
        lastAngle = laserShots[currentIndex].angle;
        laserShots.erase(laserShots.begin() + currentIndex);
    }

    std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
    getchar();
    return 0;
}