#ifndef ADVENTOFCODE2024_DAY21
#define ADVENTOFCODE2024_DAY21

#include "../includes/aoc.h"
#include <algorithm>

class Day21 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct Robot {
        uint8_t current_pos = 'A';
        std::map<int8_t, v2> index;
        std::map<v2, int8_t> index_r;
        std::map<v2, std::string> direction_lookup;

        Robot() {
            index['0'] = v2(1, 3);
            index['1'] = v2(0, 2);
            index['2'] = v2(1, 2);
            index['3'] = v2(2, 2);
            index['4'] = v2(0, 1);
            index['5'] = v2(1, 1);
            index['6'] = v2(2, 1);
            index['7'] = v2(0, 0);
            index['8'] = v2(1, 0);
            index['9'] = v2(2, 0);
            index['A'] = v2(2, 3);
                 
            index_r[v2(1, 3)] = '0';
            index_r[v2(0, 2)] = '1';
            index_r[v2(1, 2)] = '2';
            index_r[v2(2, 2)] = '3';
            index_r[v2(0, 1)] = '4';
            index_r[v2(1, 1)] = '5';
            index_r[v2(2, 1)] = '6';
            index_r[v2(0, 0)] = '7';
            index_r[v2(1, 0)] = '8';
            index_r[v2(2, 0)] = '9';
            index_r[v2(2, 3)] = 'A';

            direction_lookup[v2(1, 0)] = ">";
            direction_lookup[v2(-1, 0)] = "<";
            direction_lookup[v2(0, -1)] = "^";
            direction_lookup[v2(0, 1)] = "v";
        }

        std::vector<std::string> get_paths(int8_t start, int8_t end)
        {
            std::string s_start = "";
            std::vector<std::string> result;

            std::queue<std::pair<v2, std::string>> l;

            l.push(std::make_pair(index[start], s_start));

            auto neighbours = MapHelper::getNeighboursVec(false);

            int8_t min_length = std::numeric_limits<int8_t>::max();
            while (!l.empty())
            {
                auto pair = l.front(); l.pop();

                if (pair.second.size() > min_length)
                    continue;

                if (index_r[pair.first] == end)
                {
                    min_length = pair.second.size();
                    result.push_back(pair.second + "A");
                    continue;
                }

                for (auto dir : neighbours)
                    if (index_r.count(pair.first + dir) > 0)
                        l.push(std::make_pair(pair.first + dir, pair.second + direction_lookup[dir]));
            }

            return result;
        }
    };

    struct Robot_Directions {
        uint8_t current_pos = 'A';
        std::map<int8_t, v2> index;
        std::map<v2, int8_t> index_r;
        std::map<v2, std::string> direction_lookup;

        Robot_Directions()
        {
            index['^'] = v2(1, 0);
            index['A'] = v2(2, 0);
            index['<'] = v2(0, 1);
            index['v'] = v2(1, 1);
            index['>'] = v2(2, 1);

            index_r[v2(1, 0)] = '^';
            index_r[v2(2, 0)] = 'A';
            index_r[v2(0, 1)] = '<';
            index_r[v2(1, 1)] = 'v';
            index_r[v2(2, 1)] = '>';

            direction_lookup[v2(1, 0)] = ">";
            direction_lookup[v2(-1, 0)] = "<";
            direction_lookup[v2(0, -1)] = "^";
            direction_lookup[v2(0, 1)] = "v";
        }

        std::vector<std::string> get_paths(int8_t start, int8_t end)
        {
            std::string s_start = "";
            std::vector<std::string> result;

            std::queue<std::pair<v2, std::string>> l;

            l.push(std::make_pair(index[start], s_start));

            auto neighbours = MapHelper::getNeighboursVec(false);

            int8_t min_length = std::numeric_limits<int8_t>::max();
            while (!l.empty())
            {
                auto pair = l.front(); l.pop();

                if (index_r[pair.first] == end)
                {
                    result.push_back(pair.second);
                    continue;
                }

                if (pair.second.size() > min_length)
                    continue;

                for (auto dir : neighbours)
                {
                    if (index_r.count(pair.first + dir) > 0)
                        l.push(std::make_pair(pair.first + dir, pair.second + direction_lookup[dir]));
                }
            }

            return result;
        }
    };

    int64_t part1()
    {
        int64_t result = 0;

        for (auto line : inputVector)
        {
            Robot numbers;
            Robot_Directions direct;
            int8_t start = 'A';

            for (int32_t index = 0; index < line.size(); ++index)
            {
                auto path = numbers.get_paths(start, line[index]);
                start = line[index];

                int32_t min_length = std::numeric_limits<int32_t>::max();

            }
        }

        Robot test;
        auto result = test.get_paths('A', 0);
        result = test.get_paths(0, 2);
        result = test.get_paths(2, 9);
        result = test.get_paths(9, 'A');
        return 0;
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day21()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_21.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_21.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY21