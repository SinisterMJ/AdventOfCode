#ifndef ADVENTOFCODE2019_DAY10
#define ADVENTOFCODE2019_DAY10

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"

class Day10 {
private:
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

	int64_t gcd(int64_t a, int64_t b)
	{
		if (b == 0)
			return a;
		return gcd(b, a % b);
	}

	std::vector<std::string> input;
public:
	Day10()
	{
		input = util::readFileLines("..\\inputs\\2019\\input_10.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		Map2DBase<int8_t> asteroids('.');
		Map2DBase<int32_t> asteroidCount(0);
		
		for (int y = 0; y < input.size(); ++y)
		{
			for (int x = 0; x < input[y].length(); ++x)
			{
				asteroids.write(x, y, input[y][x]);
				asteroidCount.write(x, y, 0);
			}
		}

		int32_t maxAsteroids = 0;
		v2 laserPos;

		for (int32_t y = 0; y < asteroids.height(); ++y)
		{
			for (int32_t x = 0; x < asteroids.width(); ++x)
			{
				v2 basePos(x, y);
				if (asteroids.read(basePos) == '#')
				{
					for (int32_t search_y = y; search_y < asteroids.height(); ++search_y)
					{
						for (int32_t search_x = (y == search_y) ? x + 1 : 0; search_x < asteroids.width(); ++search_x)
						{
							v2 searchPos(search_x, search_y);

							if (asteroids.read(searchPos) == '#')
							{
								int64_t ggt = gcd(std::abs(searchPos.x - basePos.x), std::abs(searchPos.y - basePos.y));
								v2 vec((searchPos - basePos) / ggt);
								v2 curPos = basePos + vec;
								bool isVisible = true;
								for (; curPos != searchPos; curPos += vec)
								{
									if (asteroids.read(curPos) == '#')
									{
										isVisible = false;
										break;
									}
								}

								if (isVisible)
								{
									asteroidCount.inc(basePos, 1);
									asteroidCount.inc(searchPos, 1);
								}
							}
						}
					}

					int currentSeen = asteroidCount.read(basePos);
					if (maxAsteroids < currentSeen)
					{
						laserPos = basePos;
						maxAsteroids = currentSeen;
					}
				}
			}
		}

		std::cout << "Day 10 - Part 1: " << maxAsteroids << std::endl;

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
				std::cout << "Day 10 - Part 2: " << laserShots[currentIndex].pos.x * 100 + laserShots[currentIndex].pos.y << std::endl;
			}

			lastIndex = currentIndex;
			lastAngle = laserShots[currentIndex].angle;
			laserShots.erase(laserShots.begin() + currentIndex);
			if (currentIndex == laserShots.size())
				currentIndex = 0;
		}

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY10