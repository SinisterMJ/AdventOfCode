#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

struct Moon {
	v3 position;
	v3 velocity;

	struct Status {
		v3 position;
		v3 velocity;
	};
	std::vector<Status> pastStatus;

	Moon(int x, int y, int z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void storeState()
	{
		Status now;
		now.position = position;
		now.velocity = velocity;

		pastStatus.push_back(now);
	}

	void changeVelocity(const Moon& other)
	{
		velocity.x += position.x < other.position.x;
		velocity.y += position.y < other.position.y;
		velocity.z += position.z < other.position.z;

		velocity.x -= position.x > other.position.x;
		velocity.y -= position.y > other.position.y;
		velocity.z -= position.z > other.position.z;
	}

	void move()
	{
		position = position + velocity;
	}
	
	std::vector<int64_t> getCircular(int index)
	{
		Status now;
		now.position = position;
		now.velocity = velocity;

		std::vector<int64_t> result;
		for (int64_t i = 0; i < pastStatus.size() - 1; ++i)
		{
			if (now.position[index] == pastStatus[i].position[index] && now.velocity[index] == pastStatus[i].velocity[index])
				result.push_back(i);
		}

		return result;
	}

	int64_t energy()
	{
		int64_t kinEnergy = std::abs(velocity.x) + std::abs(velocity.y) + std::abs(velocity.z);
		int64_t posEnergy = std::abs(position.x) + std::abs(position.y) + std::abs(position.z);
		return kinEnergy * posEnergy;
	}
};

int64_t gcd(int64_t a, int64_t b)
{
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int64_t lcm(int64_t a, int64_t b)
{
	return (a * b) / gcd(a, b);
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFileLines("..\\inputs\\input_2019_12.txt");
	//std::vector<std::string> input;
	//input.push_back("<x=-8, y=-10, z=0>");
	//input.push_back("<x=5, y=5, z=10>");
	//input.push_back("<x=2, y=-7, z=3>");
	//input.push_back("<x=9, y=-8, z=-3>");
	std::vector<Moon> moons;
	
	for (auto elem : input)
	{
		int offset = elem.find(",");
		int offsetVar = elem.find("x=");
		int x = std::stoi(elem.substr(offsetVar + 2, offset - offsetVar - 2));
		offset = elem.find(",", offset);
		offsetVar = elem.find("y=");
		int y = std::stoi(elem.substr(offsetVar + 2, offset - offsetVar - 2));
		offset = elem.find(",", offset);
		offsetVar = elem.find("z=");
		int z = std::stoi(elem.substr(offsetVar + 2, offset - offsetVar - 2));
		moons.push_back(Moon(x, y, z));
	}

	int64_t periodic[3];
	periodic[0] = -1;
	periodic[1] = -1;
	periodic[2] = -1;

	for (int sim = 0; ; ++sim)
	{
		if (sim == 2771)
		{
			int breakHere = 0;
		}
		if (sim == 1000)
		{
			int64_t result = 0;

			for (int i = 0; i < moons.size(); ++i)
			{
				result += moons[i].energy();
			}

			std::cout << result << std::endl;
		}

		for (int i = 0; i < moons.size(); ++i)
		{
			moons[i].storeState();
		}

		for (int i = 0; i < moons.size(); ++i)
		{
			for (int j = i + 1; j < moons.size(); ++j)
			{
				moons[i].changeVelocity(moons[j]);
				moons[j].changeVelocity(moons[i]);
			}
		}

		for (int i = 0; i < moons.size(); ++i)
		{
			moons[i].move();
		}

		std::vector<std::vector<int64_t>> previous[3];
		for (int j = 0; j < 3; ++j) 
		{
			for (int i = 0; i < moons.size(); ++i)
			{
				previous[j].push_back(moons[i].getCircular(j));
			}
		}

		int64_t seenInAll = -1;

		for (int j = 0; j < 3; ++j)
		{
			if (periodic[j] != -1)
			{
				continue;
			}
			for (auto elem : previous[j][0])
			{
				bool seenInAll = true;
				for (int i = 0; i < previous[j].size(); ++i)
				{
					if (std::find(previous[j][i].begin(), previous[j][i].end(), elem) == previous[j][i].end())
					{
						seenInAll = false;
					}
				}
				if (seenInAll)
				{
					periodic[j] = sim + 1;
					std::cout << "Periodic " << j << ": " << sim + 1 << std::endl;
				}
			}
		}

		if (periodic[0] != -1 && periodic[1] != -1 && periodic[2] != -1)
		{
			std::cout << "Part 2: " << lcm(periodic[0], lcm(periodic[1], periodic[2])) << std::endl;
			break;
		}
	}

	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}