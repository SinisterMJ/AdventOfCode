#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <regex>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

struct Moon {
	v3 position;
	v3 velocity;

	struct Status {
		v3 position;
		v3 velocity;
	};
	
    Status initial;

	Moon(int x, int y, int z) : position(x, y, z) 
    {
	    initial.position = position;
        initial.velocity = velocity;
	}

	void changeVelocity(Moon& other)
	{
        for (int index = 0; index < 3; ++index)
        {
            velocity[index] += position[index] < other.position[index];
            velocity[index] -= position[index] > other.position[index];
        }
	}

    void move()
	{
		position += velocity;
	}
	
	bool getCircular(int index)
	{
        return  (position[index] == initial.position[index]) && 
                (velocity[index] == initial.velocity[index]);
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

int64_t getTotalEnergy(std::vector<Moon>& moons)
{
    int64_t result = 0;
    for (int i = 0; i < moons.size(); ++i)
        result += moons[i].energy();

    return result;
}

void performStep(std::vector<Moon>& moons)
{
    for (int i = 0; i < moons.size(); ++i)
    {
        for (int j = i + 1; j < moons.size(); ++j)
        {
            moons[i].changeVelocity(moons[j]);
            moons[j].changeVelocity(moons[i]);
        }
    }

    for (int i = 0; i < moons.size(); ++i)
        moons[i].move();
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFileLines("..\\inputs\\input_2019_12.txt");
	
    std::vector<Moon> moons;
    int64_t periodic[3] = { -1, -1, -1 };
    
    std::regex moon_regex("x=(.*), y=(.*), z=(.*)>");
    std::smatch moon_match;
	for (auto elem : input)
	{
        if (std::regex_search(elem, moon_match, moon_regex) && moon_match.size() >= 4)
            moons.push_back(Moon(std::stoi(moon_match[1]), std::stoi(moon_match[2]), std::stoi(moon_match[3])));
	}
    
	for (int sim = 0;; ++sim)
	{
		if (sim == 1000)
		    std::cout << "Part 1: " << getTotalEnergy(moons) << std::endl;
		
        performStep(moons);

		for (int dimension = 0; dimension < 3; ++dimension)
		{
			if (periodic[dimension] != -1)
				continue;

            bool periodicByDimension = true;

            for (int i = 0; i < moons.size(); ++i)
                periodicByDimension &= moons[i].getCircular(dimension);
            
            if (periodicByDimension)
				periodic[dimension] = sim + 1;
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