#ifndef ADVENTOFCODE2020_DAY22
#define ADVENTOFCODE2020_DAY22

#include "../includes/aoc.h"
#include <unordered_set>
#include <deque>

class Day22
{
private:
    int64_t part1()
    {
        int64_t result = 0;
        std::deque<int64_t> deck_1;
        std::deque<int64_t> deck_2;

        for (auto elem : player_1)
        {
            deck_1.push_back(elem);
        }

        for (auto elem : player_2)
        {
            deck_2.push_back(elem);
        }

        while (deck_1.size() > 0 && deck_2.size() > 0)
        {
            int64_t val_1 = deck_1.front(); deck_1.pop_front();
            int64_t val_2 = deck_2.front(); deck_2.pop_front();

            if (val_1 > val_2)
            {
                deck_1.push_back(val_1);
                deck_1.push_back(val_2);
            }

            if (val_1 < val_2)
            {
                deck_2.push_back(val_2);
                deck_2.push_back(val_1);
            }
        }

        std::deque<int64_t> finalDeck;

        if (deck_1.size() > 0)
            finalDeck = deck_1;
        else
            finalDeck = deck_2;

        for (; finalDeck.size() > 0; )
        {
            result += finalDeck.size() * finalDeck.front();
            finalDeck.pop_front();
        }

        return result;
    }

    int64_t getHistory(std::deque<int64_t>& deck)
    {
        int64_t hist = 0;
        for (int index = 0; index < deck.size(); ++index)
            hist += primes[index] * deck[index];

        return hist;
    }

    bool playRound(std::deque<int64_t>& deck_1, std::deque<int64_t>& deck_2)
    {
        std::set< std::pair<int64_t, int64_t> > history_int;
        while (deck_1.size() > 0 && deck_2.size() > 0)
        {
            int64_t hist_1 = getHistory(deck_1);
            int64_t hist_2 = getHistory(deck_2);
            
            auto currentHist_int = std::make_pair(hist_1, hist_2);
            
            // Rule 1 of recursive combat
            if (history_int.find(currentHist_int) != history_int.end())
                return true;

            history_int.insert(currentHist_int);

            int64_t val_1 = deck_1.front();
            int64_t val_2 = deck_2.front();

            deck_1.pop_front();
            deck_2.pop_front();

            bool player_1_wins = val_1 > val_2;;
            // Enter recursive combat
            if (val_1 <= deck_1.size() && val_2 <= deck_2.size())
            {
                std::deque<int64_t> sub_1(deck_1.begin(), deck_1.begin() + val_1);
                std::deque<int64_t> sub_2(deck_2.begin(), deck_2.begin() + val_2);

                player_1_wins = playRound(sub_1, sub_2);
            }

            if (player_1_wins)
            {
                deck_1.push_back(val_1);
                deck_1.push_back(val_2);
            }
            else
            {
                deck_2.push_back(val_2);
                deck_2.push_back(val_1);
            }
        }

        return deck_1.size() > 0;
    }

    int64_t part2()
    {
        int64_t result = 0;
        std::deque<int64_t> deck_1(player_1.begin(), player_1.end());
        std::deque<int64_t> deck_2(player_2.begin(), player_2.end());
        std::deque<int64_t> finalDeck = playRound(deck_1, deck_2) ? deck_1 : deck_2;
                
        for (; finalDeck.size() > 0; )
        {
            result += finalDeck.size() * finalDeck.front();
            finalDeck.pop_front();
        }

        return result;
    }

    std::vector<int64_t> player_1;
    std::vector<int64_t> player_2;

    std::vector<int64_t> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229 };
    std::string inputString;
    std::vector<std::string> inputVec;
public:
    Day22()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_22.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_22.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        bool player_two = false;
        for (auto elem : inputVec)
        {
            if (elem == "Player 2:")
            {
                player_two = true;
            }

            if (elem.find("Player") != std::string::npos)
            {
                continue;
            }

            int64_t val = std::stoll(elem);

            if (player_two)
                player_2.push_back(val);
            else
                player_1.push_back(val);
        }

        int64_t result_1 = part1();
        int64_t result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 22 - Part 1: " << result_1 << '\n'
                  << "Day 22 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY22
