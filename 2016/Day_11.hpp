#ifndef ADVENTOFCODE2016_DAY11
#define ADVENTOFCODE2016_DAY11

#include "../includes/aoc.h"
#include <regex>
#include <set>

class Day11 {
private:
	std::vector<std::string> inputVec;

    struct Element {
        std::string identifier;
        bool generator = false;
    };

    int elevator_level = 1;

    std::map<int, std::vector<Element>> floor_state;

    // The first floor contains a strontium generator, a strontium-compatible microchip, a plutonium generator, and a plutonium-compatible microchip.
    void read_floors()
    {
        int floor = 0;
        std::regex generator("([a-z]+) generator");
        std::regex microchip("([a-z]+)-compatible microchip");
        
        for (auto ln : inputVec)
        {
            floor++;
            std::regex_token_iterator<std::string::iterator> it_gen(ln.begin(), ln.end(), generator, 1);
            std::regex_token_iterator<std::string::iterator> rend;

            while (it_gen != rend)
            {
                Element entry;
                entry.identifier = (*it_gen);
                entry.generator = true;

                floor_state[floor].push_back(entry);
                it_gen++;
            }

            std::regex_token_iterator<std::string::iterator> it_mc(ln.begin(), ln.end(), microchip, 1);

            while (it_mc != rend)
            {
                Element entry;
                entry.identifier = (*it_mc);

                floor_state[floor].push_back(entry);
                it_mc++;
            }
        }
    }

    std::pair<int, std::map<int, std::vector<Element>>> valid_moves(int elevator, std::map<int, std::vector<Element>> floors)
    {
        return std::pair<int, std::map<int, std::vector<Element>>>();
    }

    int part1()
    {
        read_floors();
        int steps{ 0 };

        std::set<std::pair<int, std::map<int, std::vector<Element>>>> seen;

        // seen.insert(std::make_pair(elevator_level, floor_state));

        while (true)
        {

        }
        return steps;
    }

    int part2()
    {
        int steps{ 0 };
        return steps;
    }

public:
	Day11()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_11.txt");
	}
    
    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();
        
        int64_t time = myTime.usPassed();

        std::cout << "Day 11 - Part 1: " << result_1 << '\n'
                  << "Day 11 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2016_DAY11