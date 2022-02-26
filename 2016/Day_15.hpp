#ifndef ADVENTOFCODE2016_DAY15
#define ADVENTOFCODE2016_DAY15

#include "../includes/aoc.h"
#include <regex>

class Day15 
{
private:

    struct ingredient {
        std::string name;
        int64_t capacity;
        int64_t durability;
        int64_t flavor;
        int64_t texture;
        int64_t calories;
    };

    std::vector<ingredient> list;

    int64_t part1()
    {
        std::regex reg("(\\S+): capacity (-?[0-9]+), durability (-?[0-9]+), flavor (-?[0-9]+), texture (-?[0-9]+), calories (-?[0-9]+)");
        std::smatch ingred_match;

        for (auto line : inputVec)
        {
            std::regex_search(line, ingred_match, reg);

            ingredient entry;

            entry.name = ingred_match[1];
            entry.capacity = std::stoi(ingred_match[2]);
            entry.durability = std::stoi(ingred_match[3]);
            entry.flavor = std::stoi(ingred_match[4]);
            entry.texture = std::stoi(ingred_match[5]);
            entry.calories = std::stoi(ingred_match[6]);

            list.push_back(entry);
        }

        int64_t max = 0;

        for (int a = 0; a <= 100; a++)
        {
            for (int b = 0; b <= 100 - a; ++b)
            {
                for (int c = 0; c <= 100 - a - b; ++c)
                {
                    int d = 100 - a - b - c;
                        
                    int64_t cap = list[0].capacity * a + list[1].capacity * b + list[2].capacity * c + list[3].capacity * d;
                    int64_t dur = list[0].durability * a + list[1].durability * b + list[2].durability * c + list[3].durability * d;
                    int64_t fla = list[0].flavor * a + list[1].flavor * b + list[2].flavor * c + list[3].flavor * d;
                    int64_t tex = list[0].texture * a + list[1].texture * b + list[2].texture * c + list[3].texture * d;

                    cap = cap < 0 ? 0 : cap;
                    dur = dur < 0 ? 0 : dur;
                    fla = fla < 0 ? 0 : fla;
                    tex = tex < 0 ? 0 : tex;

                    int64_t res = cap * dur * fla * tex;
                    max = std::max(res, max);
                }
            }
        }

        return max;
    }

    int64_t part2()
    {        
        int64_t max = 0;

        for (int a = 0; a <= 100; a++)
        {
            for (int b = 0; b <= 100 - a; ++b)
            {
                for (int c = 0; c <= 100 - a - b; ++c)
                {
                    int d = 100 - a - b - c;
                    
                    int64_t cal = list[0].calories * a + list[1].calories * b + list[2].calories * c + list[3].calories * d;
                    if (cal != 500)
                        continue;

                    int64_t cap = list[0].capacity * a + list[1].capacity * b + list[2].capacity * c + list[3].capacity * d;
                    int64_t dur = list[0].durability * a + list[1].durability * b + list[2].durability * c + list[3].durability * d;
                    int64_t fla = list[0].flavor * a + list[1].flavor * b + list[2].flavor * c + list[3].flavor * d;
                    int64_t tex = list[0].texture * a + list[1].texture * b + list[2].texture * c + list[3].texture * d;
                    
                    cap = cap < 0 ? 0 : cap;
                    dur = dur < 0 ? 0 : dur;
                    fla = fla < 0 ? 0 : fla;
                    tex = tex < 0 ? 0 : tex;
                    
                    int64_t res = cap * dur * fla * tex;
                    max = std::max(res, max);
                }
            }
        }

        return max;
    }

	std::vector<std::string> inputVec;
public:
	Day15()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_15.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		int64_t result1 = part1();
        int64_t result2 = part2();

		std::cout << "Day 15 - Part 1: " << result1 << std::endl
				  << "Day 15 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY15