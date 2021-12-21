#ifndef ADVENTOFCODE2021_DAY21
#define ADVENTOFCODE2021_DAY21

#include "../includes/aoc.h"

class Day21 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;
    
    int32_t start_player1;
    int32_t start_player2;

    int64_t part1()
    {
        int32_t pos_1 = start_player1;
        int32_t pos_2 = start_player2;

        int32_t points_1 = 0;
        int32_t points_2 = 0;

        int32_t die = 1;

        while (true)
        {
            for (int i = 0; i < 3; ++i)
            {
                pos_1 += die;
                die++;
            }

            pos_1 = (pos_1 - 1) % 10 + 1;
            points_1 += pos_1;

            if (points_1 >= 1000)
                break;

            for (int i = 0; i < 3; ++i)
            {
                pos_2 += die;
                die++;
            }
            
            pos_2 = (pos_2 - 1) % 10 + 1;
            points_2 += pos_2;

            if (points_2 >= 1000)
                break;
        }

        if (points_1 >= 1000)
            return points_2 * (die - 1);
        else
            return points_1 * (die - 1);
    }

    /*
    3: 111
    4: 112 211 121
    5: 113 131 311 122 212 221
    6: 123 132 321 312 213 231 222
    7: 133 313 331 223 232 322
    8: 233 323 332
    9: 333
    */


    std::array<int8_t, 10> paths{ -1, -1, -1, 1, 3, 6, 7, 6, 3, 1 };

    void recursive(int pos_1, int pos_2, int32_t points_1, int32_t points_2, bool player1_turn, int64_t pathsToHere, int64_t& wins_player1, int64_t& wins_player2)
    {
        if (player1_turn)
        {
            for (int i = 3; i <= 9; ++i)
            {
                auto newPos = pos_1;
                newPos += i;

                if (newPos > 10)
                    newPos -= 10;

                auto new_score_1 = points_1 + newPos;
                if (new_score_1 >= 21)
                    wins_player1 += pathsToHere * paths[i];
                else
                    recursive(newPos, pos_2, new_score_1, points_2, false, pathsToHere * paths[i], wins_player1, wins_player2);
            }
        }
        else
        {
            for (int i = 3; i <= 9; ++i)
            {
                auto newPos = pos_2;
                newPos += i;

                if (newPos > 10)
                    newPos -= 10;

                auto new_score_2 = points_2 + newPos;
                if (new_score_2 >= 21)
                    wins_player2 += pathsToHere * paths[i];
                else
                    recursive(pos_1, newPos, points_1, new_score_2, true, pathsToHere * paths[i], wins_player1, wins_player2);
            }
        }
    }

    int64_t part2()
    {
        int64_t wins_1 = 0;
        int64_t wins_2 = 0;

        recursive(start_player1, start_player2, 0, 0, true, 1, wins_1, wins_2);

        return std::max(wins_1, wins_2);
    }

public:
    Day21()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_21.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_21.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        start_player1 = std::stoi(inputVec[0].substr(std::string("Player 1 starting position: ").size()));
        start_player2 = std::stoi(inputVec[1].substr(std::string("Player 2 starting position: ").size()));

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 21 - Part 1: " << result_1 << '\n'
            << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
