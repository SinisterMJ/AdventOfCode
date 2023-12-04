#ifndef ADVENTOFCODE2023_DAY04
#define ADVENTOFCODE2023_DAY04

#include "../includes/aoc.h"
#include <algorithm>

class Day04 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    int64_t part1()
    {
        int result = 0;
        for (auto line : inputVector)
        {
            auto game = util::split(line, ':');
            auto numbers = util::split(game[1], '|');

            std::set<int> winning, drawn;
            
            auto winNumbers = util::split(numbers[0], ' ');

            for (auto num : winNumbers)
                if (num != "")
                    winning.insert(std::stoi(num));
            
            auto drawNumbers = util::split(numbers[1], ' ');
            int gameWin = 0;

            for (auto num : drawNumbers)
            {
                if (num != "")
                {
                    if (winning.find(std::stoi(num)) != winning.end())
                    {
                        if (gameWin == 0)
                            gameWin = 1;
                        else
                            gameWin *= 2;
                    }
                }
            }
                        
            result += gameWin;
        }
        return result;
    }

    int64_t part2()
    {
        int64_t result = 0;
        std::map<int, int64_t> scratch_cards;

        int game_index = 1;
        for (auto line : inputVector)
        {
            scratch_cards[game_index] += 1;

            auto game = util::split(line, ':');
            auto numbers = util::split(game[1], '|');

            std::set<int> winning, drawn;

            auto winNumbers = util::split(numbers[0], ' ');

            for (auto num : winNumbers)
                if (num != "")
                    winning.insert(std::stoi(num));

            auto drawNumbers = util::split(numbers[1], ' ');
            int gameWin = 0;

            for (auto num : drawNumbers)
                if (num != "")
                    if (winning.find(std::stoi(num)) != winning.end())
                        gameWin += 1;
            
            for (int index = 1; index <= gameWin; ++index)
                scratch_cards[game_index + index] += scratch_cards[game_index];

            game_index++;
        }

        for (int index = 1; index <= inputVector.size(); ++index)
        {
            result += scratch_cards[index];
        }

        return result;
    }

public:
    Day04()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_4.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY04