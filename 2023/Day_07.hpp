#ifndef ADVENTOFCODE2023_DAY07
#define ADVENTOFCODE2023_DAY07

#include "../includes/aoc.h"
#include <algorithm>

class Day07 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    std::map<int8_t, int8_t> cardStrength;
    
    struct CamelCards {
        std::string cards;
        int bid;
        int8_t rank;


        CamelCards() {
            bid = 0;
            rank = 0;
            cards = "";
        }

        int8_t rankLevel(bool part_2)
        {
            std::map<int8_t, int8_t> occurences;
            std::vector<int8_t> occs;

            for (auto ch : cards)
                occurences[ch] += 1;

            int8_t num_j = 0;

            for (auto [ch, occ] : occurences)
            {
                if (part_2 && ch == 'J')
                {
                    num_j = occ;
                    continue;
                }
                occs.push_back(occ);
            }

            std::sort(occs.rbegin(), occs.rend());

            if (num_j == 5)
                occs.push_back(0);

            occs[0] += num_j;

            if (occs == std::vector<int8_t>{5})
                return 7;

            if (occs == std::vector<int8_t>{4, 1})
                return 6;

            if (occs == std::vector<int8_t>{3, 2})
                return 5;

            if (occs == std::vector<int8_t>{3, 1, 1})
                return 4;

            if (occs == std::vector<int8_t>{2, 2, 1})
                return 3;

            if (occs == std::vector<int8_t>{2, 1, 1, 1})
                return 2;

            if (occs == std::vector<int8_t>{1, 1, 1, 1, 1})
                return 1;

            return 0;
        }
    };

    std::vector<CamelCards> allCards;

    void sortArray()
    {
        std::sort(allCards.begin(), allCards.end(), [&](const auto& a, const auto& b)
            {
                if (a.rank != b.rank)
                    return a.rank < b.rank;
                else
                    for (int index = 0; index < a.cards.size(); ++index)
                        if (a.cards[index] != b.cards[index])
                            return cardStrength[a.cards[index]] < cardStrength[b.cards[index]];

                return false;
            }
        );
    }

    int64_t part1()
    {
        cardStrength['2'] = 0;
        cardStrength['3'] = 1;
        cardStrength['4'] = 2;
        cardStrength['5'] = 3;
        cardStrength['6'] = 4;
        cardStrength['7'] = 5;
        cardStrength['8'] = 6;
        cardStrength['9'] = 7;
        cardStrength['T'] = 8;
        cardStrength['J'] = 9;
        cardStrength['Q'] = 10;
        cardStrength['K'] = 11;
        cardStrength['A'] = 12;

        for (auto line : inputVector)
        {
            auto card = util::split(line, ' ');
            CamelCards temp;
            temp.cards = card[0];
            temp.bid = std::stoi(card[1]);
            temp.rank = temp.rankLevel(false);
            allCards.push_back(temp);
        }

        sortArray();

        int64_t result = 0;
        for (int index = 0; index < allCards.size(); ++index)
            result += (index + 1) * allCards[index].bid;

        return result;
    }

    int64_t part2()
    {
        cardStrength['J'] = -1;

        for (auto& card : allCards)
            card.rank = card.rankLevel(true);

        sortArray();

        int64_t result = 0;
        for (int index = 0; index < allCards.size(); ++index)
            result += (index + 1) * allCards[index].bid;

        return result;
    }

public:
    Day07()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY07