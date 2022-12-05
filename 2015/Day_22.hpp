#ifndef ADVENTOFCODE2015_DAY22
#define ADVENTOFCODE2015_DAY22

#include "../includes/aoc.h"
#include <deque>

class Day22
{
private:
    struct magic_state {
        int magic_missile = 0;
        int drain = 0;
        int shield = 0;
        int poison = 0;
        int recharge = 0;
    };

    class Magician {
    public:
        int32_t hitpoints;
        int32_t manapoints;
        int32_t armor;

        Magician(int32_t _hp, int32_t _mana)
            : hitpoints(_hp)
            , manapoints(_mana)
            , armor(0)
        {

        }
    };

    struct Fighter {
        int32_t hitpoints;
        int32_t damage;
        Fighter() : hitpoints(0), damage(0) { }
    };

    struct State
    {
        bool character_turn;
        Magician character;
        magic_state spell;
        Fighter boss_char;
        int64_t spent_mana;
        State(int32_t _hp, int32_t _mana)
            : character(_hp, _mana)
            , spent_mana(0)
            , character_turn(true)
        { }
    };

    Fighter boss;
    Magician mag = Magician(50, 500);

    int32_t fight(bool hardmode)
    {
        std::deque<State> active_fights;
        State initial(50, 500);
        initial.boss_char = boss;
        initial.spell = magic_state();
        active_fights.push_back(initial);

        int32_t min_mana = std::numeric_limits<int32_t>::max();

        while (active_fights.size() > 0)
        {
            auto current_state = active_fights.front();
            active_fights.pop_front();

            if (current_state.spent_mana > min_mana)
                continue;

            current_state.character.hitpoints -= current_state.character_turn & hardmode;

            // Check active spells first
            if (current_state.spell.shield > 0)
            {
                current_state.spell.shield--;
                current_state.character.armor = 7;
            }
            else
            {
                current_state.character.armor = 0;
            }

            if (current_state.spell.poison > 0)
            {
                current_state.spell.poison--;
                current_state.boss_char.hitpoints -= 3;
            }

            if (current_state.spell.recharge > 0)
            {
                current_state.spell.recharge--;
                current_state.character.manapoints += 101;
            }

            if (current_state.boss_char.hitpoints <= 0)
            {
                min_mana = std::min<int64_t>(min_mana, current_state.spent_mana);
                continue;
            }

            if (current_state.character.hitpoints <= 0)
                continue;

            if (current_state.character_turn)
            {
                current_state.character_turn = false;
                State current_temp = current_state;
                // Character doesn't have enough mana for any spells, but boss is still alive
                // Fight lost.
                if (current_state.character.manapoints < 53)
                    continue;

                // Magic Missile
                if (current_state.character.manapoints >= 53)
                {
                    State current_temp = current_state;
                    current_temp.spent_mana += 53;
                    current_temp.character.manapoints -= 53;
                    current_temp.boss_char.hitpoints -= 4;
                    active_fights.push_back(current_temp);
                }

                // Drain
                if (current_state.character.manapoints >= 73)
                {
                    State current_temp = current_state;
                    current_temp.spent_mana += 73;
                    current_temp.character.manapoints -= 73;
                    current_temp.boss_char.hitpoints -= 2;
                    current_temp.character.hitpoints += 2;
                    active_fights.push_back(current_temp);
                }

                if (current_state.character.manapoints >= 113 && current_state.spell.shield == 0)
                {
                    State current_temp = current_state;
                    current_temp.spent_mana += 113;
                    current_temp.character.manapoints -= 113;
                    current_temp.spell.shield = 6;
                    active_fights.push_back(current_temp);
                }

                if (current_state.character.manapoints >= 173 && current_state.spell.poison == 0)
                {
                    State current_temp = current_state;
                    current_temp.spent_mana += 173;
                    current_temp.character.manapoints -= 173;
                    current_temp.spell.poison = 6;
                    active_fights.push_back(current_temp);
                }

                if (current_state.character.manapoints >= 229 && current_state.spell.recharge == 0)
                {
                    State current_temp = current_state;
                    current_temp.spent_mana += 229;
                    current_temp.character.manapoints -= 229;
                    current_temp.spell.recharge = 5;
                    active_fights.push_back(current_temp);
                }
            }
            else
            {
                current_state.character_turn = true;
                int32_t damage = current_state.boss_char.damage - current_state.character.armor;
                damage = std::max(damage, 1);
                current_state.character.hitpoints -= damage;
                active_fights.push_back(current_state);
            }
        }

        return min_mana;
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

        int32_t result1 = fight(false);
        int32_t result2 = fight(true);

        std::cout << "Day 22 - Part 1: " << result1 << std::endl;
        std::cout << "Day 22 - Part 2: " << result2 << std::endl;

        return myTime.usPassed();
    }
};

#endif  // ADVENTOFCODE2015_DAY22