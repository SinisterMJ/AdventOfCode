#ifndef ADVENTOFCODE2015_DAY22
#define ADVENTOFCODE2015_DAY22

#include "../includes/aoc.h"
#include <bitset>

class Day22
{
private:
    
    class Magician {
    private:
        int32_t hitpoints;
        int32_t manapoints;
    public:
        Magician(int32_t _hp, int32_t _mana)
            : hitpoints(_hp)
            , manapoints(_mana)
        {

        }
    };

    struct Fighter {
        int64_t hitpoints;
        int64_t damage;
        Fighter() : hitpoints(0), damage(0) { }
    };

    Fighter boss;

    int64_t part1()
    {
        return 0;
    }

public:
    Day22()
    {
        boss.hitpoints = 71;
        boss.damage = 10;
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t result1 = part1();
        int64_t result2 = part1();

        std::cout << "Day 22 - Part 1: " << result1 << std::endl;
        std::cout << "Day 22 - Part 2: " << result2 << std::endl;

        return myTime.usPassed();
    }
};

#endif  // ADVENTOFCODE2015_DAY22