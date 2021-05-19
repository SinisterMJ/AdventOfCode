#ifndef ADVENTOFCODE2017_DAY21
#define ADVENTOFCODE2017_DAY21

#include "../includes/aoc.h"
#include <bitset>

class Day21 
{
private:

	struct Fighter {
		int64_t hitpoints;
		int64_t armor;
		int64_t damage;
		Fighter() : hitpoints(0), armor(0), damage(0) { }
	};

	struct Item {
		int64_t armor;
		int64_t damage;
		int64_t cost;

		Item() : cost(0), armor(0), damage(0) { }
		Item(int64_t _cost, int64_t _damage, int64_t _armor) : cost(_cost), armor(_armor), damage(_damage) { }
	};

	Fighter boss;

	std::vector<Item> weapons;
	std::vector<Item> armors;
	std::vector<Item> rings;

	bool winner(Fighter character, Fighter opponent)
	{
		while (character.hitpoints > 0 && opponent.hitpoints > 0)
		{
			int64_t damage = character.damage - opponent.armor;
			if (damage <= 0)
				damage = 1;

			opponent.hitpoints -= damage;

			if (opponent.hitpoints <= 0)
				break;

			damage = opponent.damage - character.armor;
			if (damage <= 0)
				damage = 1;

			character.hitpoints -= damage;
		}

		return character.hitpoints > 0;
	}

	std::pair<int64_t, int64_t> run_battles()
	{
		int64_t min_cost = std::numeric_limits<int64_t>::max();
		int64_t max_cost = std::numeric_limits<int64_t>::min();
		Fighter standard;
		standard.armor = 0;
		standard.hitpoints = 100;
		standard.damage = 0;

		for (auto weapon : weapons)
		{
			for (uint64_t idx_armor = 0; idx_armor <= armors.size(); ++idx_armor)
			{
				for (int8_t idx_rings = 0; idx_rings <= 0x30; ++idx_rings)
				{
					int64_t cost = weapon.cost;

					Fighter character(standard);
					character.damage += weapon.damage;

					std::bitset<8> ringList(idx_rings);
					if (ringList.count() > 2)
						continue;

					if (idx_armor != armors.size())
					{
						character.armor += armors[idx_armor].armor;
						cost += armors[idx_armor].cost;
					}

					for (int index = 0; index < 6; ++index)
					{
						if (ringList[index])
						{
							character.damage += rings[index].damage;
							character.armor += rings[index].armor;
							cost += rings[index].cost;
						}
					}

					if (winner(character, boss))
					{
						min_cost = std::min(min_cost, cost);
					}
					else
					{
						max_cost = std::max(max_cost, cost);
					}
				}
			}
		}
		return std::make_pair(min_cost, max_cost);
	}

public:
	Day21()
	{
		boss.hitpoints = 109;
		boss.armor = 2;
		boss.damage = 8;

		weapons.push_back(Item(8, 4, 0));
		weapons.push_back(Item(10, 5, 0));
		weapons.push_back(Item(25, 6, 0));
		weapons.push_back(Item(40, 7, 0));
		weapons.push_back(Item(74, 8, 0));

		armors.push_back(Item(13, 0, 1));
		armors.push_back(Item(31, 0, 2));
		armors.push_back(Item(53, 0, 3));
		armors.push_back(Item(75, 0, 4));
		armors.push_back(Item(102, 0, 5));

		rings.push_back(Item(25, 1, 0));
		rings.push_back(Item(50, 2, 0));
		rings.push_back(Item(100, 3, 0));

		rings.push_back(Item(20, 0, 1));
		rings.push_back(Item(40, 0, 2));
		rings.push_back(Item(80, 0, 3));
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		auto result = run_battles();
		int64_t result1 = result.first;
		int64_t result2 = result.second;

		std::cout << "Day 21 - Part 1: " << result1 << std::endl;
		std::cout << "Day 21 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2017_DAY21