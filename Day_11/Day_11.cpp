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
	v2 pos;
	float angle;
	double distance;

	LocDistAngle(v2 d_v, v2 p)
	{
		distance = std::sqrt(d_v.x * d_v.x + d_v.y * d_v.y);
		angle = static_cast<float>(std::atan2(d_v.x, -d_v.y) / PI * 180.0);

		if (angle < 0)
			angle += 360.0;

		pos = p;
	}

	bool operator<(const LocDistAngle& b) const
	{
		if (angle != b.angle)
			return angle < b.angle;
		return distance < b.distance;
	}
};

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

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
	v2 laserPos;

	for (int32_t y = 0; y < asteroids.height(); ++y)
	{
		for (int32_t x = 0; x < asteroids.width(); ++x)
		{
			v2 basePos(x, y);
			if (asteroids.read(basePos) == '#')
			{
				int32_t numAsteroids = 0;
				for (int32_t search_y = 0; search_y < asteroids.height(); ++search_y)
				{
					for (int32_t search_x = 0; search_x < asteroids.width(); ++search_x)
					{
						v2 searchPos(search_x, search_y);
						if (searchPos == basePos)
							continue;

						if (asteroids.read(searchPos) == '#')
						{
							int32_t ggt = gcd(std::abs(search_x - x), std::abs(search_y - y));
							v2 vec((search_x - x) / ggt, (search_y - y) / ggt);
							v2 curPos = basePos + vec;
							bool isVisible = true;
							for (; curPos.x != search_x || curPos.y != search_y; curPos += vec)
							{
								if (asteroids.read(curPos) == '#')
								{
									isVisible = false;
									break;
								}
							}
							numAsteroids += isVisible;
						}
					}
				}
				if (maxAsteroids < numAsteroids)
					laserPos = basePos;

				maxAsteroids = std::max(numAsteroids, maxAsteroids);
			}
		}
	}

	std::cout << "Result Day 10 Part 1: " << maxAsteroids << std::endl;

	std::vector<LocDistAngle> laserShots;
	for (int x = 0; x < asteroids.width(); ++x)
	{
		for (int y = 0; y < asteroids.height(); ++y)
		{
			v2 basePos(x, y);
			if (basePos == laserPos)
				continue;

			if (asteroids.read(basePos) == '#')
				laserShots.push_back(LocDistAngle(basePos - laserPos, basePos));
		}
	}
	std::sort(laserShots.begin(), laserShots.end());

	float lastAngle = -1.f;
	int currentIndex = 0;
	int lastIndex = -1;
	for (int count = 1; count <= 200; ++count)
	{
		while (lastAngle == laserShots[currentIndex].angle)
		{
			currentIndex = (currentIndex + 1) % laserShots.size();

			if (lastIndex == currentIndex)
			{
				currentIndex = 0;
				break;
			}
		}

		if (count == 200)
		{
			std::cout << "Result Day 10 Part 2: " << laserShots[currentIndex].pos.x * 100 + laserShots[currentIndex].pos.y << std::endl;
		}

		lastIndex = currentIndex;
		lastAngle = laserShots[currentIndex].angle;
		laserShots.erase(laserShots.begin() + currentIndex);
		if (currentIndex == laserShots.size())
			currentIndex = 0;
	}

	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}