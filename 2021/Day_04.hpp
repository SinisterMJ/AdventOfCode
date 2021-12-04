#ifndef ADVENTOFCODE2021_DAY04
#define ADVENTOFCODE2021_DAY04

#include "../includes/aoc.h"
#include <vector>
#include <array>
#include <algorithm>
#include <set>

class Day04 {
private:

    std::vector<std::string> inputs;
    std::string input;

    std::vector<int32_t> bingodraws;
    std::vector<std::array<std::array<int32_t, 5>, 5>> bingoBoards;
    std::set<int32_t> drawn;

    void build_boards()
    {
        bingodraws = util::splitInt(inputs[0], ',');

        for (int i = 1; i < inputs.size(); i += 6)
        {
            std::array<std::array<int32_t, 5>, 5> board;
            for (int offset = 0; offset < 5; ++offset)
            {
                std::vector<int32_t> row = util::splitInt(inputs[i + 1 + offset], ' ');
                std::copy_n(row.begin(), 5, board[offset].begin());
            }

            bingoBoards.push_back(board);
        }
    }

    int64_t part1_2(bool erase)
    {
        for (auto number : bingodraws)
        {
            if (drawn.find(number) != drawn.end())
                continue;

            drawn.insert(number);
            for (int index = 0; index < bingoBoards.size(); ++index)
            {
                auto board = bingoBoards[index];

                for (int i = 0; i < 5; ++i)
                {
                    bool completeRow = true;
                    bool completeColumn = true;
                    for (int j = 0; j < 5; ++j)
                    {
                        completeRow = completeRow && (drawn.find(board[i][j]) != drawn.end());
                        completeColumn = completeColumn && (drawn.find(board[j][i]) != drawn.end());
                    }

                    if (completeRow || completeColumn)
                    {
                        if (bingoBoards.size() > 1 && erase)
                        {
                            bingoBoards.erase(bingoBoards.begin() + index);
                            --index;
                            break;
                        }

                        int32_t sum = 0;

                        for (auto& row : board)
                            for (auto& val : row)
                                sum += (drawn.find(val) != drawn.end()) ? 0 : val;

                        return sum * number;
                    }
                }
            }
        }

        return 0;
    }

public:
    Day04()
    {
        inputs = util::readFileLines("..\\inputs\\2021\\input_4.txt", '\n', false);
        input = util::readFile("..\\inputs\\2021\\input_4.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        build_boards();
        int64_t result_1 = part1_2(false);
        int64_t result_2 = part1_2(true);

        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY04